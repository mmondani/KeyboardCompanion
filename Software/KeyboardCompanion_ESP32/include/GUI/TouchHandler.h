#ifndef TOUCHHANDLER_H
#define TOUCHHANDLER_H

#include <functional>
#include <Adafruit_STMPE610.h>
#include <SoftTimers.h>
#include "../RingBuffer.h"




class TouchHandler {
    public:
        enum TouchEventType {
            CLICK,
            RELEASE
        };

        typedef struct {
            TouchEventType type;
            uint32_t x;
            uint32_t y;
        }TouchEvent;


        static TouchHandler* getInstance();
        void begin(Adafruit_STMPE610* touch, uint8_t rotation, uint32_t tftWidth, uint32_t tftHeight, RingBuffer<TouchEvent>* eventBuffer);
        void handler ();

    protected:
        TouchHandler();
        TouchHandler (TouchHandler const&);
        TouchHandler& operator= (TouchHandler const&);

    private:
        enum State
        {
            IDLE,
            DEBOUNCE_CLICK,
            CLICKED,
            DEBOUNCE_RELEASE
        };

        static TouchHandler* instance;
        static RingBuffer<TouchEvent>* touchEventBuffer;
        TouchHandler::State state;
        TouchHandler::State prevState;
        Adafruit_STMPE610* touch;
        uint8_t rotation;
        uint32_t tftWidth;
        uint32_t tftHeight;
        SoftTimer debounceTimer;
        uint16_t x, y;
        uint8_t z;

        void getRotatedXY (uint16_t* x, uint16_t* y);
        void gotoState (TouchHandler::State nextState);
};


#endif