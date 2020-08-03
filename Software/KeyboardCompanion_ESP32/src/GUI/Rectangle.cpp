#include "../../include/GUI/Rectangle.h"


Rectangle::Rectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, 
                uint32_t bgColor, bool border, uint32_t borderColor)
        : Widget(x, y, w, h) {

    this->border = border;
    clickable = false;

    this->backgroundColorRelease = new Color(bgColor);
    this->borderColorRelease = new Color(borderColor);

    this->backgroundColor = this->backgroundColorRelease;
    this->borderColor = this->borderColorRelease;

    this->backgroundColorClick = new Color();
    this->backgroundColorClick->copy(this->backgroundColor);
    this->backgroundColorClick->multiply(1, 2);
    this->borderColorClick = new Color(0xff0000);
}


void Rectangle::draw(TFT_eSPI* tft) {
    if (visible) {
        tft->fillRect(x, y, w, h, backgroundColor->to565Format());

        if (border)
            tft->drawRect(x, y, w, h, borderColor->to565Format());
    }
}


void Rectangle::clearArea(TFT_eSPI* tft) {

}


void Rectangle::onClick() {
    if (clickable) {
        backgroundColor = backgroundColorClick;
        borderColor = borderColorClick;

        show();

        emit(this->click);
    }
}


void Rectangle::onRelease() {
    if (clickable) {
        backgroundColor = backgroundColorRelease;
        borderColor = borderColorRelease;

        show();

        emit(this->release);
    }
}


void Rectangle::setBackgroundColor (uint32_t color) {
    backgroundColor->setColor(color);
    this->backgroundColorClick->copy(this->backgroundColor);
    this->backgroundColorClick->multiply(1, 2);
}


void Rectangle::setBorderColor (uint32_t color) {
    borderColor->setColor(color);
}