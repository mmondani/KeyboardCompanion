#ifndef MAINFSM_H
#define MAINFSM_H

#include <ArduinoJson.h>
#include "GUI/FSProvider.h"
#include "GUI/Widgets.h"
#include "Screens/Screens.h"
#include "GUI/GuiHandler.h"
#include "SerialLayer.h"
#include "CustomWebServer.h"


class MainFsm {
    public:
        static MainFsm* getInstance();
        void begin ();
        void handler ();


    protected:
        MainFsm();
        MainFsm (MainFsm const&);
        MainFsm& operator= (MainFsm const&);


    private:
        enum State
        {
            INIT,
            PARSE_JSON,
            IDLE,
            ERROR
        };

        void gotoState (MainFsm::State nextState);
        void showCurrentPage ();
        void processIconClicked ();

        static MainFsm* instance;
        CustomWebServer webserver;
        MainFsm::State state;
        MainFsm::State prevState;
        bool stateIn, stateOut;
        SoftTimer stateTimer;
        StaticJsonDocument<10000> jsonDoc;
        JsonObject mainJsonObject;
        JsonObject pagesJsonObject;
        JsonObject gridsJsonObject;
        JsonArray currentGridArray;
        const char* initialPage;
        const char* currentPage;
        const char* prevPage;
        const char* nextPage;

        TestScreen testScreen;
        TestScreen2 testScreen2;
        LoadingDataScreen loadingDataScreen;
        IconGridScreen iconGridScreen;

        bool navigationLeftClick;
        bool navigationMainClick;
        bool navigationRightClick;
        bool iconClick;
        uint32_t iconNumberClicked;
};


#endif