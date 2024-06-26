#include "../../include/GUI/GuiHandler.h"
#include "../../include/GUI/FSProvider.h"


GuiHandler* GuiHandler::instance = nullptr;



GuiHandler* GuiHandler::getInstance() {
    if (instance == nullptr) {

        instance = new GuiHandler();
    }
    
    return instance;
}

GuiHandler::GuiHandler() {
  touchHandler = TouchHandler::getInstance();
  touchEventBuffer = new RingBuffer<TouchHandler::TouchEvent>(10);
  widgetEventBuffer = new RingBuffer<Widget::WidgetEvent>(20);

  currentScreen = nullptr;
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
  touchHandler->begin(touch, rotation, tft->width(), tft->height(), touchEventBuffer);
}


void GuiHandler::handler() {

  touchHandler->handler();

  if (touchEventBuffer->getPending()) {
    TouchHandler::TouchEvent* event = touchEventBuffer->remove();

    if (event->type == TouchHandler::TouchEventType::CLICK) {
      tft->fillCircle(event->x, event->y, 2, TFT_BLACK); 

      /*
      Serial.print("click: ");
      Serial.print(event->x);
      Serial.print(" ");
      Serial.println(event->y);
      */

      if (currentScreen != nullptr)
        currentScreen->onClick(event->x, event->y);
    }
    else if (event->type == TouchHandler::TouchEventType::RELEASE) {
      /*
      Serial.print("release: ");
      Serial.print(event->x);
      Serial.print(" ");
      Serial.println(event->y);
      */
      if (currentScreen != nullptr)
        currentScreen->onRelease(event->x, event->y);
    }
  }

  if (widgetEventBuffer->getPending()) {
    Widget::WidgetEvent* event = widgetEventBuffer->remove();

    if (event->type == Widget::WidgetEventType::DRAW)
      event->widget->draw(tft);
    else if (event->type == Widget::WidgetEventType::HIDE) {
      if (currentScreen != nullptr)
        currentScreen->show();
    }
  }
}


void GuiHandler::setScreen(Screen* screen) {  
  currentScreen = screen;
  currentScreen->show();
}


bool GuiHandler::isRenderingScreen () {
  bool ret = false;

  if (widgetEventBuffer->getPending())
    ret = true;

  return ret;
}