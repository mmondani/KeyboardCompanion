#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Widget.h"
#include "Color.h"


class Rectangle : public Widget {
    public:
        Rectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, 
                    uint32_t bgColor = 0, bool border = false, uint32_t borderColor = 0);
        void draw(TFT_eSPI* tft);
        void clearArea(TFT_eSPI* tft);
        void onClick();
        void onRelease();
        void setBackgroundColor (uint32_t color);
        void setBorder (bool border);
        void setBorderColor (uint32_t color);

    protected:

    private:
        bool border;
        Color* backgroundColor; 
        Color* borderColor;
        Color* backgroundColorClick; 
        Color* borderColorClick;
};


#endif