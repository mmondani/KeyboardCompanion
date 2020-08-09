#ifndef ICONGRIDSCREEN_H
#define ICONGRIDSCREEN_H

#include <stdint.h>
#include "../GUI/Widgets.h"
#include "../GUI/Screen.h"
#include "../GUI/FSProvider.h"


namespace IconGridScreenCallbacks 
{
    enum NavigationEvent {
        LEFT,
        RIGHT,
        MAIN
    };

    typedef std::function<void(uint32_t iconNumber)> IconClick;
    typedef std::function<void(NavigationEvent event)> NavigationClick;
}


class IconGridScreen : public Screen {
    public:
        IconGridScreen(FSProvider* fsProvider);
        void setIcon (uint32_t iconNumber, const char* fileName);
        void setIconClickCallback (IconGridScreenCallbacks::IconClick callback);
        void setNavigationEventCallback (IconGridScreenCallbacks::NavigationClick callback);

    private:    
        Widget* widgetList[14];
        Rectangle background;
        IconButton iconButton0;
        IconButton iconButton1;
        IconButton iconButton2;
        IconButton iconButton3;
        IconButton iconButton4;
        IconButton iconButton5;
        IconButton iconButton6;
        IconButton iconButton7;
        IconButton iconButton8;
        Rectangle headerBackground;
        Label leftLabel;
        Label titleLabel;
        Label rightLabel;

        IconGridScreenCallbacks::IconClick iconClickCallback;
        IconGridScreenCallbacks::NavigationClick navigationEventCallback;
};


#endif