#include "../../include/GUI/GuiHandler.h"



GuiHandler* GuiHandler::instance = nullptr;


GuiHandler* GuiHandler::getInstance() {
    if (instance == nullptr)
        instance = new GuiHandler();
    
    return instance;
}

GuiHandler::GuiHandler() {
  touchHandler = TouchHandler::getInstance();
  tsEvent = NONE;
}


void GuiHandler::begin(TFT_eSPI* tft, Adafruit_STMPE610* touch, uint8_t rotation, uint16_t tftWidth, uint16_t tftHeight) {
    this->tft = tft;
    this->touch = touch;
    this->rotation = rotation;
    this->tftWidth = tftWidth;
    this->tftHeight = tftHeight;

    tft->setRotation(rotation);

    touchHandler->begin(touch, rotation, tftWidth, tftHeight);
    touchHandler->setOnTouchCallback([this] (uint32_t x, uint32_t y) {
        this->ts_x = x;
        this->ts_y = y;
        this->tsEvent = CLICK;
        Serial.print("callback click: ");
        Serial.print(ts_x);
        Serial.print(" ");
        Serial.println(ts_y);
    });

    touchHandler->setOnReleaseCallback([this] (void) {
        this->tsEvent = RELEASE;
    });
}


void GuiHandler::handler() {

    touchHandler->handler();


    if (tsEvent != NONE) {
      Serial.print("event: ");
      Serial.println(tsEvent);

      if (tsEvent == CLICK) {
        Serial.print("click: ");
        Serial.print(ts_x);
        Serial.print(" ");
        Serial.println(ts_y);
        tft->fillCircle(ts_x, ts_y, 2, TFT_BLACK); 
      }

      tsEvent = NONE;
    }
}
