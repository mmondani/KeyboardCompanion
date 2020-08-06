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


    this->backgroundColorRelease = new Color(bgColor);
    this->borderColorRelease = new Color(borderColor);
    this->textColorRelease = new Color(textColor);

    this->backgroundColor = this->backgroundColorRelease;
    this->borderColor = this->borderColorRelease;
    this->textColor = this->borderColorRelease;

    this->backgroundColorClick = new Color();
    this->backgroundColorClick->copy(this->backgroundColor);
    this->backgroundColorClick->multiply(1, 2);             // Color más oscuro
    this->borderColorClick = new Color(0xff0000);
    this->textColorClick = new Color();
    this->textColorClick->copy(this->textColor);
    this->textColorClick->multiply(3, 1);                   // Color más claro
}


void Label::draw(TFT_eSPI* tft) {
    uint32_t textWidth;
    uint32_t tCursorX, tCursorY;
    char* c;


    if (visible) {

        if (background)
            tft->fillRect(x, y, w, h, backgroundColor->to565Format());

        if (border)
            tft->drawRect(x, y, w, h, borderColor->to565Format());


        if (text != nullptr) {
            tft->setTextColor(textColor->to565Format());
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


void Label::onClick() {
    if (clickable) {
        backgroundColor = backgroundColorClick;
        borderColor = borderColorClick;
        textColor = textColorClick;

        show();

        emit(this->click);
    }
}


void Label::onRelease() {
    if (clickable) {
        backgroundColor = backgroundColorRelease;
        borderColor = borderColorRelease;
        textColor = textColorRelease;

        show();

        emit(this->release);
    }
}


void Label::setBackgroundColor (uint32_t color) {
    backgroundColor->setColor(color);
    this->backgroundColorClick->copy(this->backgroundColor);
    this->backgroundColorClick->multiply(1, 2);
}


void Label::setBorderColor (uint32_t color) {
    borderColor->setColor(color);
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