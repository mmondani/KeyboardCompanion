#ifndef TESTSCREEN_H
#define TESTSCREEN_H

#include <stdint.h>
#include "../GUI/Widgets.h"


class TestScreen {
    public:
        TestScreen();
        void show();
        void hide();
        void onClick(uint32_t x, uint32_t y);
        void onRelease(uint32_t x, uint32_t y);

    private:    
        Rectangle background;
        Rectangle rect1;
        Rectangle rect2;
};


#endif