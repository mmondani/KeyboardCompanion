#include "../../include/GUI/Widget.h"


RingBuffer<Widget::WidgetEvent>* Widget::widgetEventBuffer = nullptr;


Widget::Widget(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    visible = true;
    clickable = true;
    clicked = false;
}


void Widget::setWidgetEventBuffer(RingBuffer<Widget::WidgetEvent>* buffer) {
    widgetEventBuffer = buffer;
}


void Widget::setVisible (const bool& v) {
    visible = v;

    /*
    if (v)
        show();
    else
        hide();
        */
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
        event->type = Widget::WidgetEventType::HIDE;
    }
}


void Widget::onClick() {

    if (clickable && visible) {
        clicked = true;

        show();

        emit(this->click);
    }
}


void Widget::onRelease() {
    if (clickable && visible) {
        clicked = false;

        show();

        emit(this->release);
    }
}


void Widget::connect (WidgetSignal& signal, SignalSlot slot) {
    signal.add(slot);
}


void Widget::emit (WidgetSignal& signal) {
    WidgetSignal* sig = &signal;

    while (sig != nullptr) {
        if (sig->getSlot() != nullptr)
            sig->getSlot() (this);

        sig = sig->getNext();
    }
}



Widget::WidgetSignal::WidgetSignal() {
    this->slot = nullptr;
    this->next = nullptr;
}


Widget::WidgetSignal::WidgetSignal(SignalSlot slot) {
    this->slot = slot;
    this->next = nullptr;
}


void Widget::WidgetSignal::add(SignalSlot slot) {
    this->next = new WidgetSignal(slot);
}


Widget::WidgetSignal* Widget::WidgetSignal::getNext() {
    return next;
}


Widget::SignalSlot Widget::WidgetSignal::getSlot() {
    return slot;
}