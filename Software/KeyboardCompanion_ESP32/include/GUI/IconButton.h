#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <stdint.h>
#include "Widget.h"
#include "Color.h"
#include "FSProvider.h"


class IconButton : public Widget {
    public:
        IconButton(uint32_t x, uint32_t y, uint32_t w, uint32_t h, FSProvider* fsProvider, char* fileName = nullptr);
        void draw(TFT_eSPI* tft);
        void clearArea(TFT_eSPI* tft);
        void setFsProvider(FSProvider* provider) { this->fsProvider = provider; };
        const FSProvider* getFsProvider () const { return fsProvider; };
        void setFileName(const char* fileName);
        const char* getFileName() const { return fileName; }; 

    private:
        void jpegRender(TFT_eSPI* tft);

        FSProvider* fsProvider;
        char fileName[20];
};


#endif