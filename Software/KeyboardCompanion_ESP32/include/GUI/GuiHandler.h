#ifndef GUIHANDLER_H
#define GUIHANDLER_H

#include <TFT_eSPI.h>
#include <Adafruit_STMPE610.h>
#include "TouchHandler.h"

class GuiHandler {
    public:
        static GuiHandler* getInstance();
        void begin(TFT_eSPI* tft, Adafruit_STMPE610* touch, uint8_t rotation, uint16_t tftWidth, uint16_t tftHeight);
        void handler();

    protected:
        GuiHandler();
        GuiHandler (GuiHandler const&);
        GuiHandler& operator= (GuiHandler const&);


    private:
        enum TsEvent {
            NONE,
            CLICK,
            RELEASE
        };

        static GuiHandler* instance;
        TouchHandler* touchHandler;
        TFT_eSPI* tft;
        Adafruit_STMPE610* touch;
        uint8_t rotation;
        uint16_t tftWidth;
        uint16_t tftHeight;

        GuiHandler::TsEvent tsEvent;
        uint32_t ts_x, ts_y;
};



#endif