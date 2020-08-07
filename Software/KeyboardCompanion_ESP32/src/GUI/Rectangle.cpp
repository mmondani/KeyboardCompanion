#include "../../include/GUI/Rectangle.h"


Rectangle::Rectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, 
                uint32_t bgColor, bool border, uint32_t borderColor)
        : Widget(x, y, w, h) {

    this->border = border;
    clickable = false;

    this->backgroundColor = bgColor;
    this->borderColor = borderColor;
}


void Rectangle::draw(TFT_eSPI* tft) {
    if (visible) {
        if (clicked)
            tft->fillRect(x, y, w, h, Color::to565Format(Color::scale(backgroundColor, 1, 2)));
        else
            tft->fillRect(x, y, w, h, Color::to565Format(backgroundColor));

        if (border) {
            if (clicked)
                tft->drawRect(x, y, w, h, Color::to565Format(0xff0000));
            else
                tft->drawRect(x, y, w, h, Color::to565Format(borderColor));
        }
    }
}


void Rectangle::clearArea(TFT_eSPI* tft) {

}


void Rectangle::setBackgroundColor (uint32_t color) {
    backgroundColor = color;
}


void Rectangle::setBorderColor (uint32_t color) {
    borderColor = color;
}