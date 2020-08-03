#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

class Color {
    public:
        Color ();
        Color (uint8_t r, uint8_t g, uint8_t b, uint8_t alpha = 0);
        Color (uint32_t color);
        static uint32_t to565Format(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha = 0);
        static uint32_t to565Format(uint32_t color);
        uint32_t to565Format();
        void setColor (uint8_t r, uint8_t g, uint8_t b, uint8_t alpha = 0);
        void setColor (uint32_t color);
        void multiply (uint32_t num, uint32_t den);
        void copy (const Color& C);
        void copy (const Color* C);

    private:
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t alpha;
};


#endif