#include "../../include/GUI/GuiHandler.h"



GuiHandler* GuiHandler::instance = nullptr;


GuiHandler* GuiHandler::getInstance() {
    if (instance == nullptr)
        instance = new GuiHandler();
    
    return instance;
}

GuiHandler::GuiHandler() {
  touchHandler = TouchHandler::getInstance();
  touchEventBuffer = new RingBuffer<TouchEvent>(10);
}


void GuiHandler::begin(TFT_eSPI* tft, Adafruit_STMPE610* touch, uint8_t rotation, uint16_t tftWidth, uint16_t tftHeight) {
    this->tft = tft;
    this->touch = touch;
    this->rotation = rotation;
    this->tftWidth = tftWidth;
    this->tftHeight = tftHeight;

    tft->setRotation(rotation);

    touchHandler->begin(touch, rotation, tftWidth, tftHeight, touchEventBuffer);
}


void GuiHandler::handler() {

    touchHandler->handler();

    if (touchEventBuffer->getPending()) {
      TouchEvent* event = touchEventBuffer->remove();

      if (event->type == TouchEventType::CLICK) {
        tft->fillCircle(event->x, event->y, 2, TFT_BLACK); 
      }
    }

}
