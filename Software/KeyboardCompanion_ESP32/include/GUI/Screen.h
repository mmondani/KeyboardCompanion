#ifndef SCREEN_H
#define SCREEN_H

#include "Widget.h"


class Screen {
    public:
        Screen(Widget** widgetList, uint32_t listSize);
        void show();
        void hide();
        void onClick(uint32_t x, uint32_t y);
        void onRelease(uint32_t x, uint32_t y);

    protected:
        Widget** widgetList;
        uint32_t widgetListSize;
};



#endif