#include "../../include/GUI/Rectangle.h"


Rectangle::Rectangle(TFT_eSPI* tft, uint32_t x, uint32_t y, uint32_t w, uint32_t h, 
                uint32_t bgColor, bool border, uint32_t borderColor)
        : Widget(tft, x, y, w, h) {

    this->backgroundColor = new Color(bgColor);
    this->border = border;
    this->borderColor = new Color(borderColor);
}


void Rectangle::draw() {
    tft->fillRect(x, y, w, h, backgroundColor->toTftColor());

    if (border)
        tft->drawRect(x, y, w, h, borderColor->toTftColor());
}


void Rectangle::clearArea() {

}


void Rectangle::onClick() {

}


void Rectangle::onRelease() {

}


void Rectangle::setBackgroundColor (uint32_t color) {
    backgroundColor->setColor(color);
}


void Rectangle::setBorder (bool border) {
    this->border = border;
}


void Rectangle::setBorderColor (uint32_t color) {
    borderColor->setColor(color);
}