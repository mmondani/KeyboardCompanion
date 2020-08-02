#include "../../include/GUI/Rectangle.h"


Rectangle::Rectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, 
                uint32_t bgColor, bool border, uint32_t borderColor)
        : Widget(x, y, w, h) {

    this->border = border;
    this->backgroundColor = new Color(bgColor);
    this->borderColor = new Color(borderColor);
    this->backgroundColorClick = new Color();
    this->backgroundColorClick->copy(this->backgroundColor);
    this->backgroundColorClick->multiply(1, 2);
    this->borderColorClick = new Color(0xff0000);
}


void Rectangle::draw(TFT_eSPI* tft) {
    tft->fillRect(x, y, w, h, backgroundColor->to565Format());

    if (border)
        tft->drawRect(x, y, w, h, borderColor->to565Format());
}


void Rectangle::clearArea(TFT_eSPI* tft) {

}


void Rectangle::onClick() {

}


void Rectangle::onRelease() {

}


void Rectangle::setBackgroundColor (uint32_t color) {
    backgroundColor->setColor(color);
    this->backgroundColorClick->copy(this->backgroundColor);
    this->backgroundColorClick->multiply(1, 2);
}


void Rectangle::setBorder (bool border) {
    this->border = border;
}


void Rectangle::setBorderColor (uint32_t color) {
    borderColor->setColor(color);
}