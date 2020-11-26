#pragma once


#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>



class CustomWebServer {     
    public:             
        CustomWebServer ();
        void begin ();
        void end ();
    
    private:
        AsyncWebServer server;
        void setRoutes ();
};