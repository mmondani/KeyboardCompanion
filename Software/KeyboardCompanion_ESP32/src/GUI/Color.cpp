#include "../../include/GUI/Color.h"


Color::Color () {
    this->r = 0;
    this->g = 0;
    this->b = 0;
    this->alpha = 0;
}


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


uint32_t Color::to565Format(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) {
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


uint32_t Color::to565Format(uint32_t color) {
    return to565Format((color & 0x00FF0000) >> 16, (color & 0x0000FF00) >> 8, (color & 0x000000FF), (color & 0xFF000000) >> 24);
}


uint32_t Color::to565Format() {
    return to565Format(r, g, b, alpha);
}


uint32_t Color::scale (uint32_t color, uint32_t num, uint32_t den) {
    uint32_t r, g, b;

    r = (color & 0x00FF0000) >> 16;
    g = (color & 0x0000FF00) >> 8;
    b = (color & 0x000000FF);

    r = (r * num) / den;
    if (r > 255)
        r = 255;

    g = (g * num) / den;
    if (g > 255)
        g = 255;

    b = (b * num) / den;
    if (b > 255)
        b = 255;

    return ((r << 16) | (g << 8) | b);
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


void Color::multiply (uint32_t num, uint32_t den) {
    uint32_t aux;

    aux = (this->r * num) / den;
    if (aux > 255)
        aux = 255;
    this->r = aux;

    aux = (this->g * num) / den;
    if (aux > 255)
        aux = 255;
	this->g = aux;

    aux = (this->b * num) / den;
    if (aux > 255)
        aux = 255;
	this->b = aux;
}


void Color::copy (const Color& C) {
    r = C.r;
    g = C.g;
    b = C.b;
    alpha = C.alpha;
}


void Color::copy (const Color* C) {
    r = C->r;
    g = C->g;
    b = C->b;
    alpha = C->alpha;
}
