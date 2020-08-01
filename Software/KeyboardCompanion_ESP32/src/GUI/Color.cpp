#include "../../include/GUI/Color.h"


Color::Color (uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->alpha = alpha;
}


Color::Color (uint32_t color) {
    this->alpha = (color & 0xFF000000) >> 24;
    this->r = (color & 0x00FF0000) >> 16;
    this->g = (color & 0x0000FF00) >> 8;
    this->b = (color & 0x000000FF);
}


uint32_t Color::toTftColor(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) {
    /**
     * El formato del color es para la librería TFT_eSPI
     * Tiene el siguiente formato:
     * 
     *    R     G      B
     *  00000 000000 00000 
     * 
     * Red: 5 bits
     * Green: 6 bits
     * Blue: 5 bits
     */
    uint32_t red, green, blue;

    red = r >> 3;
    red = red << 11;

    green = g >> 2;
    green = green << 5;

    blue = b >> 3;

    return (red | green | blue);

}


uint32_t Color::toTftColor(uint32_t color) {
    return toTftColor((color & 0x00FF0000) >> 16, (color & 0x0000FF00) >> 8, (color & 0x000000FF), (color & 0xFF000000) >> 24);
}


uint32_t Color::toTftColor() {
    return toTftColor(r, g, b, alpha);
}


void Color::setColor (uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->alpha = alpha;
}


void Color::setColor (uint32_t color) {
    this->alpha = (color & 0xFF000000) >> 24;
    this->r = (color & 0x00FF0000) >> 16;
    this->g = (color & 0x0000FF00) >> 8;
    this->b = (color & 0x000000FF);
}