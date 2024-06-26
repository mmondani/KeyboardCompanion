#ifndef TESTSCREEN_H
#define TESTSCREEN_H

#include <stdint.h>
#include "../GUI/Widgets.h"
#include "../GUI/Screen.h"
#include "../GUI/FSProvider.h"


namespace TestScreenCallbacks 
{
    typedef std::function<void(void)> IconClick;
}


class TestScreen : public Screen {
    public:
        TestScreen(FSProvider* fsProvider);
        void setIconClickCallback (TestScreenCallbacks::IconClick callback);

    private:    
        Widget* widgetList[6];
        Rectangle background;
        Rectangle rect1;
        Rectangle rect2;
        Label label1;
        Button button1;
        IconButton iconButton1;

        TestScreenCallbacks::IconClick iconClickCallback;
};


#endif