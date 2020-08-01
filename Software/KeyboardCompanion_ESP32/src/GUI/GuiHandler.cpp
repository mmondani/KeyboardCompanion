#include "../../include/GUI/GuiHandler.h"

// Valores de calibración genéricos para el touch
#define TS_MINX 220
#define TS_MINY 140
#define TS_MAXX 3900
#define TS_MAXY 3750


GuiHandler* GuiHandler::instance = nullptr;


GuiHandler* GuiHandler::getInstance() {
    if (instance == nullptr)
        instance = new GuiHandler();
    
    return instance;
}

GuiHandler::GuiHandler() {

}


void GuiHandler::begin(TFT_eSPI* tft, Adafruit_STMPE610* touch, uint8_t rotation, uint16_t tftWidth, uint16_t tftHeight) {
    this->tft = tft;
    this->touch = touch;
    this->rotation = rotation;
    this->tftWidth = tftWidth;
    this->tftHeight = tftHeight;

    tft->setRotation(rotation);
}


void GuiHandler::handler() {
    uint16_t x, y;
    uint8_t z;


    if (touch->touched())
    {
        while (!touch->bufferEmpty()) {
            Serial.print(touch->bufferSize());
            touch->readData(&x, &y, &z);
            
            getRotatedXY(&x, &y);

            tft->fillCircle(x, y, 2, TFT_BLACK); 

        }
    }
}





void GuiHandler::getRotatedXY (uint16_t* x, uint16_t* y) {
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