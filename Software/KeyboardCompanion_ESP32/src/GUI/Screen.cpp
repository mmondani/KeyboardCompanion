#include "../../include/GUI/Screen.h"


Screen::Screen(Widget** widgetList, uint32_t listSize) {
    this->widgetList = widgetList;
    widgetListSize = listSize;
}


void Screen::show() {
    for (uint32_t i = 0; i < widgetListSize; i ++)
        widgetList[i]->show();
}


void Screen::hide() {
    for (uint32_t i = 0; i < widgetListSize; i ++)
        widgetList[i]->hide();
}


void Screen::onClick(uint32_t x, uint32_t y) {
    for (uint32_t i = 0; i < widgetListSize; i ++) {
        if (widgetList[i]->containsPoint(x, y))
            widgetList[i]->onClick();
    }
}


void Screen::onRelease(uint32_t x, uint32_t y) {
    for (uint32_t i = 0; i < widgetListSize; i ++) {
        if (widgetList[i]->containsPoint(x, y))
            widgetList[i]->onRelease();
    }
}