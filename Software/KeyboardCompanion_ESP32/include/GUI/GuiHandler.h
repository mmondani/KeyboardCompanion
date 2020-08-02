#ifndef GUIHANDLER_H
#define GUIHANDLER_H

#include <TFT_eSPI.h>
#include <Adafruit_STMPE610.h>
#include "TouchHandler.h"
#include "Widgets.h"
#include "../RingBuffer.h"


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
        static GuiHandler* instance;
        RingBuffer<TouchEvent>* touchEventBuffer;
        RingBuffer<Widget::WidgetEvent>* widgetEventBuffer;
        TouchHandler* touchHandler;
        TFT_eSPI* tft;
        Adafruit_STMPE610* touch;
        uint8_t rotation;
        uint16_t tftWidth;
        uint16_t tftHeight;
};



#endif