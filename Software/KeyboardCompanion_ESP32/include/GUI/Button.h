#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"
#include "Color.h"
#include "Label.h"


class Button : public Label {
    public:
        Button (uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t textSize, char* text = nullptr, TextHAlign align = TextHAlign::LEFT,
                    uint32_t textColor = 0, bool background = true, uint32_t bgColor = 0, bool border = false, uint32_t borderColor = 0);

        void draw(TFT_eSPI* tft);
        void clearArea(TFT_eSPI* tft);

    private:
};


#endif