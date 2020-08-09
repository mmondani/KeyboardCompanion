#ifndef LOADINGDATASCREEN_H
#define LOADINGDATASCREEN_H

#include <stdint.h>
#include "../GUI/Widgets.h"
#include "../GUI/Screen.h"
#include "../GUI/FSProvider.h"


class LoadingDataScreen : public Screen {
    public:
        LoadingDataScreen();

    private:    
        Widget* widgetList[2];
        Rectangle background;
        Label label1;
};


#endif