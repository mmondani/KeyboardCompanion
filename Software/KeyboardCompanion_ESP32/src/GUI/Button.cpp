#include "../../include/GUI/Button.h"


Button::Button (uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t textSize, char* text, TextHAlign align,
                    uint32_t textColor, bool background, uint32_t bgColor, bool border, uint32_t borderColor)
            : Label(x, y, w, h, textSize, text, align, textColor, background, bgColor, border, borderColor) {

    clickable = true;
}

void Button::draw(TFT_eSPI* tft) {
    uint32_t textWidth;
    uint32_t tCursorX, tCursorY;
    uint32_t hAux;
    uint32_t hAcum = 0;
    char* c;

    if (visible) {

        if (background) {
            if (clicked) {
                hAux = h * 1 / 12;
                for (uint32_t i = 0; i < 4; i++) {
                    tft->fillRect(x, y + hAcum, w, hAux, Color::to565Format(Color::scale(backgroundColor, 6+i, 10)));
                    hAcum += hAux;
                }

                hAux = h * 2 / 3;
                tft->fillRect(x, y + hAcum, w, hAux, Color::to565Format(backgroundColor));
                hAcum += hAux;
            }
            else {
                hAux = h * 2 / 3;
                tft->fillRect(x, y, w, hAux, Color::to565Format(backgroundColor));
                hAcum += hAux;

                hAux = h * 1 / 12;
                for (uint32_t i = 0; i < 4; i++) {
                    tft->fillRect(x, y + hAcum, w, hAux, Color::to565Format(Color::scale(backgroundColor, 9-i, 10)));
                    hAcum += hAux;
                }

                if (hAcum < h)
                    tft->fillRect(x, y + hAcum, w, h - hAcum, Color::to565Format(Color::scale(backgroundColor, 6, 10)));
            }
        }

        if (border) {
            if (clicked) 
                tft->drawRect(x, y, w, h, Color::to565Format(0xff0000));
            else
                tft->drawRect(x, y, w, h, Color::to565Format(borderColor));
        }


        if (text != nullptr) {
            tft->setTextColor(Color::to565Format(textColor));

            tft->setTextSize(textSize);
            
            // Posición del texto dentro del label
            textWidth = tft->textWidth(this->text);
            if (textWidth <= w) {
                if (textHAlign == TextHAlign::LEFT)
                    tCursorX = x + 2;
                else if (textHAlign == TextHAlign::CENTER)
                    tCursorX = x + ((w - textWidth) / 2);  
                else
                    tCursorX = x + (w - textWidth);  
            }   
            else
                tCursorX = x + 2;

            tCursorY = y + (((h + 1) - textSize * 7) / 2);		// Centrado vertical

        
            for (c = this->text; *c != '\0'; c++) {
                if ((tCursorX + 6 * textSize) <= (x + w)) {
                    tft->drawChar(*c, tCursorX, tCursorY);
                    tCursorX = tCursorX + 6 * textSize;
                }
                else
                    break;
            }
            
        }
    }
}


void Button::clearArea(TFT_eSPI* tft) {

}