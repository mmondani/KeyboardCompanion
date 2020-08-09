#include <JPEGDecoder.h>
#include "../../include/GUI/IconButton.h"


IconButton::IconButton(uint32_t x, uint32_t y, uint32_t w, uint32_t h, FSProvider* fsProvider, char* fileName) 
            : Widget(x, y, w, h) {

    clickable = true;
    this->fsProvider = fsProvider;

    if (fileName != nullptr)  {
        if (fileName[0] != '/') {
            this->fileName[0] = '/';
            strcpy(&(this->fileName[1]), fileName);
        }
        else
            strcpy(this->fileName, fileName);
    }
    else
        this->fileName[0] = '\0';
}


void IconButton::draw(TFT_eSPI* tft) {
    fs::FS* fileSystem;

    
    if (visible) {
        fileSystem = fsProvider->take();

        if (fileSystem != nullptr) {
            
            fs::File jpegFile = fileSystem->open(fileName, FILE_READ);
            
            if ( !jpegFile ) {
                Serial.print("ERROR: File \""); Serial.print(fileName); Serial.println ("\" not found!");
            }
            else {
                bool decoded = JpegDec.decodeSdFile(jpegFile);

                if (decoded) {
                    jpegRender(tft);
                }
                else
                    Serial.println("Jpeg file format not supported!");

                if (clicked)
                    tft->drawRect(x, y, w, h, Color::to565Format(COLOR_ACCENT));
            } 
            
            fsProvider->give();
        }
        else {
            // Si no se puede acceder al FS se vuelve a disparar el método show
            // hasta que se pueda acceder
            this->show();
        }
    }
    
}


void IconButton::clearArea(TFT_eSPI* tft) {

}


void IconButton::setFileName(const char* fileName) {
   
    if (fileName != nullptr)  {
        if (fileName[0] != '/') {
            this->fileName[0] = '/';
            strcpy(&(this->fileName[1]), fileName);
        }
        else
            strcpy(this->fileName, fileName);
    }
    else
        this->fileName[0] = '\0';
}



void IconButton::jpegRender(TFT_eSPI* tft) {

    uint16_t *pImg;
    uint16_t mcu_w = JpegDec.MCUWidth;
    uint16_t mcu_h = JpegDec.MCUHeight;
    uint32_t max_x = JpegDec.width;
    uint32_t max_y = JpegDec.height;

    bool swapBytes = tft->getSwapBytes();
    tft->setSwapBytes(true);

    // Jpeg images are draw as a set of image block (tiles) called Minimum Coding Units (MCUs)
    // Typically these MCUs are 16x16 pixel blocks
    // Determine the width and height of the right and bottom edge image blocks
    uint32_t min_w = min<int>(mcu_w, max_x % mcu_w);
    uint32_t min_h = min<int>(mcu_h, max_y % mcu_h);

    // save the current image block size
    uint32_t win_w = mcu_w;
    uint32_t win_h = mcu_h;

    // save the coordinate of the right and bottom edges to assist image cropping
    // to the screen size
    max_x += x;
    max_y += y;

    // Fetch data from the file, decode and display
    while (JpegDec.read()) {    // While there is more data in the file
        pImg = JpegDec.pImage ;   // Decode a MCU (Minimum Coding Unit, typically a 8x8 or 16x16 pixel block)

        // Calculate coordinates of top left corner of current MCU
        int mcu_x = JpegDec.MCUx * mcu_w + x;
        int mcu_y = JpegDec.MCUy * mcu_h + y;

        // check if the image block size needs to be changed for the right edge
        if (mcu_x + mcu_w <= max_x) win_w = mcu_w;
        else win_w = min_w;

        // check if the image block size needs to be changed for the bottom edge
        if (mcu_y + mcu_h <= max_y) win_h = mcu_h;
        else win_h = min_h;

        // copy pixels into a contiguous block
        if (win_w != mcu_w) {
            uint16_t *cImg;
            int p = 0;
            cImg = pImg + win_w;
            for (int h = 1; h < win_h; h++) {
                p += mcu_w;
                for (int w = 0; w < win_w; w++) {
                    *cImg = *(pImg + w + p);
                    cImg++;
                }
            }
        }

        // calculate how many pixels must be drawn
        uint32_t mcu_pixels = win_w * win_h;

        // draw image MCU block only if it will fit on the screen
        if (( mcu_x + win_w ) <= tft->width() && ( mcu_y + win_h ) <= tft->height())
            tft->pushImage(mcu_x, mcu_y, win_w, win_h, pImg);
        else if ( (mcu_y + win_h) >= tft->height())
            JpegDec.abort(); // Image has run off bottom of screen so abort decoding
    }

    tft->setSwapBytes(swapBytes);
}