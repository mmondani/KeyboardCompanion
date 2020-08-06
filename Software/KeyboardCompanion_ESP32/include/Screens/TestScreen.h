#ifndef TESTSCREEN_H
#define TESTSCREEN_H

#include <stdint.h>
#include "../GUI/Widgets.h"
#include "../GUI/Screen.h"


class TestScreen : public Screen {
    public:
        TestScreen();

    private:    
        Widget* widgetList[4];
        Rectangle background;
        Rectangle rect1;
        Rectangle rect2;
        Label label1;
};


#endif