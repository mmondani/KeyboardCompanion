#include "../include/MainFsm.h"


MainFsm* MainFsm::instance = nullptr;


MainFsm* MainFsm::getInstance() {
    if (instance == nullptr)
        instance = new MainFsm();
    
    return instance;
}


MainFsm::MainFsm() 
      : testScreen(FSProvider::getInstance()),
      testScreen2(FSProvider::getInstance()),
      loadingDataScreen(),
      iconGridScreen(FSProvider::getInstance()) {

    state = INIT;
    prevState = INIT;

    stateIn = true;
    stateOut = false;
}


void MainFsm::begin () {

    iconGridScreen.setIconClickCallback([this](uint32_t iconNumber) {
        Serial.print("Icono: ");
        Serial.println(iconNumber);
    });


    iconGridScreen.setNavigationEventCallback([this](IconGridScreenCallbacks::NavigationEvent event) {
        switch(event) {
            case IconGridScreenCallbacks::NavigationEvent::LEFT: Serial.println(F("Navigation - Left")); break;
            case IconGridScreenCallbacks::NavigationEvent::MAIN: Serial.println(F("Navigation - Main")); break;
            case IconGridScreenCallbacks::NavigationEvent::RIGHT: Serial.println(F("Navigation - RIGHT")); break;
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
                        const char* initialPage = mainJsonObject["initial_page"];
                        pagesJsonObject = mainJsonObject["pages"];
                        gridsJsonObject = mainJsonObject["grids"];

                        if (!initialPage)
                            Serial.println(F("Error initial_page"));
                        else {
                            Serial.print(F("initial_page: "));
                            Serial.println(initialPage);
                        }
                        if (pagesJsonObject.isNull())
                            Serial.println(F("Error pages"));
                        if (gridsJsonObject.isNull())
                            Serial.println(F("Error grids"));

                        if (initialPage && !pagesJsonObject.isNull() && !gridsJsonObject.isNull()) {
                            currentPage = initialPage;

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

            }
            /*******************************************************************/

            /*******************************************************************/
            if (stateOut) {
                stateOut = false;
                stateIn = true;

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
            const char* gridNumber = pageJsonObject["grid"];

            Serial.print(F("Tipo de page: "));
            Serial.println(pageJsonObject["type"].as<const char*>());

            Serial.print(F("Numero de grid: "));
            Serial.println(gridNumber);

            if (gridNumber) {
                JsonArray gridArray = gridsJsonObject[gridNumber];

                if (!gridArray.isNull()) {
                    Serial.print(F("Grid size: "));
                    Serial.println(gridArray.size());

                    for (uint32_t i = 0; i < gridArray.size(); i++) {
                        JsonObject gridElement = gridArray[i];
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