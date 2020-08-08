#include "../../include/GUI/Label.h"


Label::Label(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t textSize, char* text, TextHAlign align,
                uint32_t textColor, bool background, uint32_t bgColor, bool border, uint32_t borderColor)
        : Widget(x, y, w, h) {

    this->border = border;
    this->background = background;
    clickable = false;

    this->textSize = textSize;
    this->textHAlign = align;

    if (text != nullptr)
        strcpy(this->text, text);
    else
        this->text[0] = '\0';


    this->backgroundColor = bgColor;
    this->borderColor = borderColor;
    this->textColor = textColor;

}


void Label::draw(TFT_eSPI* tft) {
    uint32_t textWidth;
    uint32_t tCursorX, tCursorY;
    char* c;


    if (visible) {

        if (background) {
            if (clicked)
                tft->fillRect(x, y, w, h, Color::to565Format(Color::scale(backgroundColor, 1, 2)));
            else
                tft->fillRect(x, y, w, h, Color::to565Format(backgroundColor));
        }

        if (border) {
            if (clicked) 
                tft->drawRect(x, y, w, h, Color::to565Format(COLOR_ACCENT));
            else
                tft->drawRect(x, y, w, h, Color::to565Format(borderColor));
        }


        if (text != nullptr) {
            if (clicked)
                tft->setTextColor(Color::to565Format(Color::scale(textColor, 3, 1)));
            else
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


void Label::clearArea(TFT_eSPI* tft) {

}




void Label::setBackgroundColor (uint32_t color) {
    backgroundColor = color;
}


void Label::setBorderColor (uint32_t color) {
    borderColor =color ;
}


void Label::setBorder(const bool& border) {
    this->border = border;
}


void Label::setBackground(const bool& background) {
    this->background = background;
}


void Label::setText(const char* text) {
    if (text != nullptr)
        strcpy(this->text, text);
    else
        this->text[0] = '\0';
}


void Label::setTextSize (const uint8_t& size) {
    this->textSize = size;
}


void Label::setTextHAlign (const TextHAlign& align) {
    this->textHAlign = align;
}