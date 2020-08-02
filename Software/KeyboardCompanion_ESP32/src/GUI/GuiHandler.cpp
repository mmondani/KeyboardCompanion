#include "../../include/GUI/GuiHandler.h"


GuiHandler* GuiHandler::instance = nullptr;



GuiHandler* GuiHandler::getInstance() {
    if (instance == nullptr)
        instance = new GuiHandler();
    
    return instance;
}

GuiHandler::GuiHandler() {
  touchHandler = TouchHandler::getInstance();
  touchEventBuffer = new RingBuffer<TouchHandler::TouchEvent>(10);
  widgetEventBuffer = new RingBuffer<Widget::WidgetEvent>(20);
}


void GuiHandler::begin(TFT_eSPI* tft, Adafruit_STMPE610* touch, uint8_t rotation, uint16_t tftWidth, uint16_t tftHeight) {
    this->tft = tft;
    this->touch = touch;
    this->rotation = rotation;
    this->tftWidth = tftWidth;
    this->tftHeight = tftHeight;

    tft->setRotation(rotation);
    tft->fillScreen(Color::to565Format(0xffffff));

    Widget::setWidgetEventBuffer(widgetEventBuffer);
    touchHandler->begin(touch, rotation, tftWidth, tftHeight, touchEventBuffer);
}


void GuiHandler::handler() {

    touchHandler->handler();

    if (touchEventBuffer->getPending()) {
      TouchHandler::TouchEvent* event = touchEventBuffer->remove();

      if (event->type == TouchHandler::TouchEventType::CLICK) {
        tft->fillCircle(event->x, event->y, 2, TFT_BLACK); 
      }
    }

    if (widgetEventBuffer->getPending()) {
      Widget::WidgetEvent* event = widgetEventBuffer->remove();

      if (event->type == Widget::WidgetEventType::DRAW)
        event->widget->draw();
      else if (event->type == Widget::WidgetEventType::CLEAR)
        event->widget->clearArea();
    }
}
