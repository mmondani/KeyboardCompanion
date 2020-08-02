#include "../../include/GUI/Widget.h"


RingBuffer<Widget::WidgetEvent>* Widget::widgetEventBuffer = nullptr;


Widget::Widget(TFT_eSPI* tft, uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    this->tft = tft;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}


void Widget::setWidgetEventBuffer(RingBuffer<Widget::WidgetEvent>* buffer) {
    widgetEventBuffer = buffer;
}


uint32_t Widget::getX () {
    return x;
}


uint32_t Widget::getY () {
    return y;
}


uint32_t Widget::getW () {
    return w;
}


uint32_t Widget::getH () {
    return h;
}


void Widget::setX (uint32_t x) {
    this->x = x;
}


void Widget::setY (uint32_t y) {
    this->y = y;
}


void Widget::setW (uint32_t w) {
    this->w = w;
}


void Widget::setH (uint32_t h) {
    this->h = h;
}


bool Widget::containsPoint (uint32_t x, uint32_t y) {
    return ((x >= this->x && x <= (this->x + this->w)) && ((y >= this->y && y <= (this->y + this->h))));
}


void Widget::show () {
    if (widgetEventBuffer != nullptr) {
        Widget::WidgetEvent* event = widgetEventBuffer->getFreeSlot();
        
        event->widget = this;
        event->type = Widget::WidgetEventType::DRAW;
    }
}


void Widget::hide () {
    if (widgetEventBuffer != nullptr) {
        Widget::WidgetEvent* event = widgetEventBuffer->getFreeSlot();
        
        event->widget = this;
        event->type = Widget::WidgetEventType::CLEAR;
    }
}


void Widget::connect (WidgetSignal signal, SignalSlot slot) {
    signal.add(slot);
}


void Widget::emmit (WidgetSignal signal) {
    WidgetSignal* sig = &signal;

    while (sig != nullptr) {
        if (sig->getSlot() != nullptr)
            sig->getSlot() ();

        sig = sig->getNext();
    }
}



WidgetSignal::WidgetSignal() {
    this->slot = nullptr;
    this->next = nullptr;
}


WidgetSignal::WidgetSignal(SignalSlot slot) {
    this->slot = slot;
    this->next = nullptr;
}


void WidgetSignal::add(SignalSlot slot) {
    this->next = new WidgetSignal(slot);
}


WidgetSignal* WidgetSignal::getNext() {
    return next;
}


SignalSlot WidgetSignal::getSlot() {
    return slot;
}