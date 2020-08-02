#include "../../include/GUI/TouchHandler.h"

// Valores de calibración genéricos para el touch
#define TS_MINX 220
#define TS_MINY 140
#define TS_MAXX 3900
#define TS_MAXY 3750


TouchHandler* TouchHandler::instance = nullptr;
RingBuffer<TouchHandler::TouchEvent>* TouchHandler::touchEventBuffer = nullptr;


TouchHandler* TouchHandler::getInstance() {
    if (instance == nullptr)
        instance = new TouchHandler();
    
    return instance;
}


TouchHandler::TouchHandler() {
 
}


void TouchHandler::begin(Adafruit_STMPE610* touch, uint8_t rotation, uint32_t tftWidth, uint32_t tftHeight, RingBuffer<TouchEvent>* eventBuffer) {
    this->touch = touch;
    this->rotation = rotation;
    this->tftWidth = tftWidth;
    this->tftHeight = tftHeight;

    touchEventBuffer = eventBuffer;

    state = IDLE;
    prevState = IDLE;
}


void TouchHandler::handler () {
    uint16_t x, y;
    uint8_t z;

    switch (state) {
        case IDLE:
            if (touch->touched()) {
                while (!touch->bufferEmpty()) {
                    touch->readData(&x, &y, &z);
                }
                
                debounceTimer.setTimeOutTime(50);
                gotoState(DEBOUNCE_CLICK);
            }

            break;

        case DEBOUNCE_CLICK:
            if (debounceTimer.hasTimedOut()) {

                if (touch->touched()) {
                    while(touch->bufferEmpty());
                    while (!touch->bufferEmpty()) {
                        touch->readData(&x, &y, &z);
                    }

                    getRotatedXY(&x, &y);

                    if (touchEventBuffer != nullptr) {
                        TouchHandler::TouchEvent* event = touchEventBuffer->getFreeSlot();

                        if (event != nullptr) {
                            event->x = x;
                            event->y = y;
                            event->type = TouchHandler::TouchEventType::CLICK;
                        }
                    }

                    gotoState(CLICKED);
                }
                else {
                    gotoState(IDLE);
                }
            }
            break;

        case CLICKED:
            if(debounceTimer.hasTimedOut()) {
                if (touch->touched()) {
                    while (!touch->bufferEmpty()) {
                        touch->readData(&x, &y, &z);
                    }

                    debounceTimer.setTimeOutTime(10);
                }
                else {
                    debounceTimer.setTimeOutTime(50);
                    gotoState(DEBOUNCE_RELEASE);
                }
            }
            break;

        case DEBOUNCE_RELEASE:
            if (debounceTimer.hasTimedOut()) {
                if (!touch->touched()) {
                    
                    if (touchEventBuffer != nullptr) {
                        TouchHandler::TouchEvent* event = touchEventBuffer->getFreeSlot();

                        if (event != nullptr) {
                            event->x = x;
                            event->y = y;
                            event->type = TouchHandler::TouchEventType::RELEASE;
                        }
                    }

                    gotoState(IDLE);
                }
                else {
                    gotoState(CLICKED);
                }
            }
            break;
    }

    
}


void TouchHandler::getRotatedXY (uint16_t* x, uint16_t* y) {
  uint16_t aux;

  switch(rotation) {
    case 0:
      *x = map(*x, TS_MINX, TS_MAXX, 0, tftWidth);
      *y = map(*y, TS_MINY, TS_MAXY, 0, tftHeight);
      break;

    case 1:
      *x = map(*x, TS_MAXX, TS_MINX, 0, tftHeight);
      *y = map(*y, TS_MINY, TS_MAXY, 0, tftWidth);

      aux = *x;
      *x = *y;
      *y = aux;
      break;

    case 2: 
      *x = map(*x, TS_MAXX, TS_MINX, 0, tftWidth);
      *y = map(*y, TS_MAXY, TS_MINY, 0, tftHeight);
      break;

    case 3:
      *x = map(*x, TS_MINX, TS_MAXX, 0, tftHeight);
      *y = map(*y, TS_MAXY, TS_MINY, 0, tftWidth);

      aux = *x;
      *x = *y;
      *y = aux;
      break;
  }

}


void TouchHandler::gotoState (TouchHandler::State nextState) {
    prevState = state;
    state = nextState;
}