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
        void setBorderColor (uint32_t color);
        void setBorder(const bool& border) { this->border = border; };
        const bool& getBorder () const { return border; };
        void setClickable(const bool& value) { clickable = value; };
        const bool& getClickable() const { return clickable; };

        WidgetSignal click;
        WidgetSignal release;

    protected:


    private:
        bool border;
        bool clickable;
        Color* backgroundColor; 
        Color* borderColor;
        Color* backgroundColorRelease; 
        Color* borderColorRelease;
        Color* backgroundColorClick; 
        Color* borderColorClick;
};


#endif