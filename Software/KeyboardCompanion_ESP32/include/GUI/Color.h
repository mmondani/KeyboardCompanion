#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

class Color {
    public:
        Color (uint8_t r, uint8_t g, uint8_t b, uint8_t alpha = 0);
        Color (uint32_t color);
        static uint32_t toTftColor(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha = 0);
        static uint32_t toTftColor(uint32_t color);
        uint32_t toTftColor();
        void setColor (uint8_t r, uint8_t g, uint8_t b, uint8_t alpha = 0);
        void setColor (uint32_t color);

    private:
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t alpha;
};


#endif