#ifndef TESTSCREEN2_H
#define TESTSCREEN2_H

#include <stdint.h>
#include "../GUI/Widgets.h"
#include "../GUI/Screen.h"
#include "../GUI/FSProvider.h"


namespace TestScreen2Callbacks 
{
    typedef std::function<void(uint32_t iconNumber)> IconClick;
}


class TestScreen2 : public Screen {
    public:
        TestScreen2(FSProvider* fsProvider);
        void setIconClickCallback (TestScreen2Callbacks::IconClick callback);

    private:    
        Widget* widgetList[10];
        Rectangle background;
        IconButton iconButton1;
        IconButton iconButton2;
        IconButton iconButton3;
        IconButton iconButton4;
        IconButton iconButton5;
        IconButton iconButton6;
        IconButton iconButton7;
        IconButton iconButton8;
        IconButton iconButton9;

        TestScreen2Callbacks::IconClick iconClickCallback;
};


#endif