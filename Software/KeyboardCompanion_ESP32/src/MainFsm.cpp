#include "../include/MainFsm.h"


MainFsm* MainFsm::instance = nullptr;


MainFsm* MainFsm::getInstance() {
    if (instance == nullptr)
        instance = new MainFsm();
    
    return instance;
}


MainFsm::MainFsm()
      : webserver(),
      testScreen(FSProvider::getInstance()),
      testScreen2(FSProvider::getInstance()),
      loadingDataScreen(),
      iconGridScreen(FSProvider::getInstance()) {

    state = INIT;
    prevState = INIT;

    stateIn = true;
    stateOut = false;

    navigationLeftClick = false;
    navigationMainClick = false;
    navigationRightClick = false;
    iconClick = false;

    initialPage = nullptr;
    currentPage = nullptr;
    prevPage = nullptr;
    nextPage = nullptr;
}


void MainFsm::begin () {

    iconGridScreen.setIconClickCallback([this](uint32_t iconNumber) {
        Serial.print("Icono: ");
        Serial.println(iconNumber);

        iconClick = true;
        iconNumberClicked = iconNumber;
    });


    iconGridScreen.setNavigationEventCallback([this](IconGridScreenCallbacks::NavigationEvent event) {
        switch(event) {
            case IconGridScreenCallbacks::NavigationEvent::LEFT: navigationLeftClick = true; break;
            case IconGridScreenCallbacks::NavigationEvent::MAIN: navigationMainClick = true; break;
            case IconGridScreenCallbacks::NavigationEvent::RIGHT: navigationRightClick = true; break;
        }
    });
}


void MainFsm::handler () {
    FS* fileSystem;

    switch (state)
    {
        case INIT:
            if(stateIn) {
                stateIn = false;
                stateOut = false;

                GuiHandler::getInstance()->setScreen(&loadingDataScreen);
                stateTimer.setTimeOutTime(1000);
            }
            /*******************************************************************/
            if (stateTimer.hasTimedOut())
                gotoState(PARSE_JSON);
            /*******************************************************************/
            if (stateOut) {
                stateOut = false;
                stateIn = true;

            }
            break;


        case PARSE_JSON:
            if(stateIn) {
                stateIn = false;
                stateOut = false;

            }
            /*******************************************************************/
            fileSystem = FSProvider::getInstance()->take();
            if (fileSystem != nullptr) {
                File file = fileSystem->open("/data.json");

                if (file) {
                    DeserializationError error = deserializeJson(jsonDoc, file);

                    if (error) {
                        FSProvider::getInstance()->give();
                        Serial.println(F("Error al parsear el archivo JSON"));
                        gotoState(ERROR);
                    }
                    else {
                        mainJsonObject = jsonDoc.as<JsonObject>();
                        const char* initial = mainJsonObject["initial_page"];
                        pagesJsonObject = mainJsonObject["pages"];
                        gridsJsonObject = mainJsonObject["grids"];

                        if (!initial)
                            Serial.println(F("Error initial_page"));
                        else {
                            Serial.print(F("initial_page: "));
                            Serial.println(initial);
                        }
                        if (pagesJsonObject.isNull())
                            Serial.println(F("Error pages"));
                        if (gridsJsonObject.isNull())
                            Serial.println(F("Error grids"));

                        if (initial && !pagesJsonObject.isNull() && !gridsJsonObject.isNull()) {
                            currentPage = initial;
                            initialPage = initial;

                            FSProvider::getInstance()->give();
                            showCurrentPage();

                            gotoState(IDLE);
                        }
                        else {
                            FSProvider::getInstance()->give();
                            Serial.println(F("Error en el archivo data.json"));
                            gotoState(ERROR);
                        }
                    }


                    file.close();
                }
                else {
                    FSProvider::getInstance()->give();
                    Serial.println(F("No se encontró data.json en la memoria SD"));
                    gotoState(ERROR);
                }
            }
            /*******************************************************************/
            if (stateOut) {
                stateOut = false;
                stateIn = true;

            }
            break;


        case IDLE:
            if(stateIn) {
                stateIn = false;
                stateOut = false;

                // Se crea el AP
                WiFi.mode(WIFI_STA);
                WiFi.disconnect();
                WiFi.softAP("ESP32", "12345678");
                delay(2000);    // Hay que esperar dos segundos para llamar a softAPConfig. Sino, crashea!!!!
                                // https://github.com/espressif/arduino-esp32/issues/2025
                WiFi.softAPConfig(IPAddress(192,168,1,1), IPAddress(192,168,1,1), IPAddress(255,255,255,0));
                
                /*
                // Se inicia el webserver
                webserver.begin();
                */
            }
            /*******************************************************************/
            if (!GuiHandler::getInstance()->isRenderingScreen()) {
                if (navigationLeftClick) {
                    navigationLeftClick = false;

                    if (prevPage != nullptr) {
                        currentPage = prevPage;
                        showCurrentPage();
                    }
                }
                else if (navigationRightClick) {
                    navigationRightClick = false;

                    if (nextPage != nullptr) {
                        currentPage = nextPage;
                        showCurrentPage();
                    }
                }
                else if (navigationMainClick) {
                    navigationMainClick = false;

                    if (initialPage != nullptr && currentPage != initialPage) {
                        currentPage = initialPage;
                        showCurrentPage();
                    }
                }
                else if (iconClick) {
                    iconClick = false;

                    processIconClicked();
                }
            }
            /*******************************************************************/
            if (stateOut) {
                stateOut = false;
                stateIn = true;

                WiFi.softAPdisconnect();
                webserver.end();
            }
            break;

    
        case ERROR:
            if(stateIn) {
                stateIn = false;
                stateOut = false;

            }
            /*******************************************************************/

            /*******************************************************************/
            if (stateOut) {
                stateOut = false;
                stateIn = true;

            }
            break;
    }
}


void MainFsm::gotoState (MainFsm::State nextState) {
    prevState = state;
    state = nextState;

    stateIn = false;
    stateOut = true;
}


void MainFsm::showCurrentPage () {
    
    JsonObject pageJsonObject = pagesJsonObject[currentPage];

    if (!pageJsonObject.isNull()) {

        if (strcmp(pageJsonObject["type"], "grid") == 0) {
            
            const char* pageTitle = pageJsonObject["title"];
            if (pageTitle)
                iconGridScreen.setPageTitle(pageTitle);
            
           
           JsonVariant prev = pageJsonObject["prev"];
            if (!prev.isNull()) {
                iconGridScreen.setLeftNavigationVisibility(true);
                prevPage = prev.as<const char*>();
            }
            else {
                iconGridScreen.setLeftNavigationVisibility(false);
                prevPage = nullptr;
            }
            
            
            JsonVariant next = pageJsonObject["next"];
            if (!next.isNull()) {
                iconGridScreen.setRighttNavigationVisibility(true);
                nextPage = next.as<const char*>();
            }
            else {
                iconGridScreen.setRighttNavigationVisibility(false);
                nextPage = nullptr;
            }


            const char* gridNumber = pageJsonObject["grid"];

            Serial.print(F("Tipo de page: "));
            Serial.println(pageJsonObject["type"].as<const char*>());

            Serial.print(F("Numero de grid: "));
            Serial.println(gridNumber);

            if (gridNumber) {
                currentGridArray = gridsJsonObject[gridNumber];

                if (!currentGridArray.isNull()) {
                    Serial.print(F("Grid size: "));
                    Serial.println(currentGridArray.size());

                    // Se "limpian" todos los slots de la grid
                    for (uint32_t i = 0; i < 15; i++)
                        iconGridScreen.setIcon(i, nullptr);

                    // Se cargan los íconos correspondientes a la grid actual
                    for (uint32_t i = 0; i < currentGridArray.size(); i++) {
                        JsonObject gridElement = currentGridArray[i];
                        const char* iconFileName = gridElement["icon"];
                        int gridPosition = gridElement["pos"];

                        Serial.print(F("Grid position: "));
                        Serial.print(gridPosition);
                        Serial.print(F(" - "));
                        Serial.println(iconFileName);
                        
                        if (iconFileName)
                            iconGridScreen.setIcon(gridPosition, iconFileName);
                    }

                    GuiHandler::getInstance()->setScreen(&iconGridScreen);
                }
            }
        }
    }

}


void MainFsm::processIconClicked () {
    uint32_t i = 0xff;

    if (!currentGridArray.isNull()) {
        for (i = 0; i < currentGridArray.size(); i++) {
            uint32_t pos = currentGridArray[i]["pos"];

            if (pos == iconNumberClicked)
                break;
        }

        if (i != 0xff) {
            const char* type = currentGridArray[i]["type"];

            if (type) {
                if (strcmp(type, "link") == 0) {
                    const char* linkPage = currentGridArray[i]["link"];

                    if (linkPage) {
                        currentPage = linkPage;
                        showCurrentPage();
                    }
                }
                else if (strcmp(type, "string") == 0) {
                    if(!SerialLayer::getInstance()->isSendingFrame()) {
                        const char* stringToSend = currentGridArray[i]["string"];

                        if (stringToSend)
                            SerialLayer::getInstance()->sendStringFrame(currentGridArray[i]["string"]);
                    }
                }
                else if (strcmp(type, "keys") == 0) {
                    if(!SerialLayer::getInstance()->isSendingFrame()) {
                        JsonArray keysToSend = currentGridArray[i]["keys"];

                        if (!keysToSend.isNull() && keysToSend.size() > 0)
                            SerialLayer::getInstance()->sendKeysFrame(currentGridArray[i]["keys"]);
                    }
                }
                else if (strcmp(type, "macro") == 0) {
                    if(!SerialLayer::getInstance()->isSendingFrame()) {
                        JsonArray keysToSend = currentGridArray[i]["macro"];

                        if (!keysToSend.isNull() && keysToSend.size() > 0)
                            SerialLayer::getInstance()->sendMacroFrame(currentGridArray[i]["macro"]);
                    }
                }
            }
        }
    }
}