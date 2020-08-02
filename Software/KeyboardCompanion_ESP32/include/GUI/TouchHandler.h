#ifndef TOUCHHANDLER_H
#define TOUCHHANDLER_H

#include <functional>
#include <Adafruit_STMPE610.h>
#include <SoftTimers.h>


typedef std::function<void(uint32_t x, uint32_t y)> OnTouchCallback;
typedef std::function<void(void)> OnReleaseCallback;

class TouchHandler {
    public:
        static TouchHandler* getInstance();
        void begin(Adafruit_STMPE610* touch, uint8_t rotation, uint32_t tftWidth, uint32_t tftHeight);
        void setOnTouchCallback (OnTouchCallback touchCallback);
        void setOnReleaseCallback (OnReleaseCallback releaseCallback);
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
        TouchHandler::State state;
        TouchHandler::State prevState;
        Adafruit_STMPE610* touch;
        uint8_t rotation;
        OnTouchCallback onTouchCallback;
        OnReleaseCallback onReleaseCallback;
        uint32_t tftWidth;
        uint32_t tftHeight;
        SoftTimer debounceTimer;

        void getRotatedXY (uint16_t* x, uint16_t* y);
        void gotoState (TouchHandler::State nextState);
};

#endif