#ifndef LABEL_H
#define LABEL_H

#include "Widget.h"
#include "Color.h"

 
class Label : public Widget {

    public:
        Label(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t textSize, char* text = nullptr, TextHAlign align = TextHAlign::LEFT,
                    uint32_t textColor = 0, bool background = true, uint32_t bgColor = 0, bool border = false, uint32_t borderColor = 0);
        void draw(TFT_eSPI* tft);
        void clearArea(TFT_eSPI* tft);
        void onClick();
        void onRelease();
        void setBackgroundColor (uint32_t color);
        void setBorderColor (uint32_t color);
        void setBorder(const bool& border);
        const bool& getBorder () const { return border; };
        void setBackground(const bool& background);
        const bool& getBackground () const { return background; };
        void setText(const char* text);
        const char* getText() const { return text; }; 
        void setTextSize (const uint8_t& size);
        const uint8_t& getTextSize () const {return textSize;}
        void setTextHAlign (const TextHAlign& align);
        const TextHAlign& getTextHAlign () const {return textHAlign;}

    protected:


    private:
        bool border;
        bool background;
        char text[50];
        uint8_t textSize;
        TextHAlign textHAlign;
        uint32_t backgroundColor; 
        uint32_t borderColor;
        uint32_t textColor;
};


#endif