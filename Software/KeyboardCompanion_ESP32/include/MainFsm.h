#ifndef MAINFSM_H
#define MAINFSM_H

#include "GUI/FSProvider.h"
#include "GUI/Widgets.h"
#include "Screens/Screens.h"
#include "GUI/GuiHandler.h"


class MainFsm {
    public:
        static MainFsm* getInstance();
        void begin ();
        void handler ();


    protected:
        MainFsm();
        MainFsm (MainFsm const&);
        MainFsm& operator= (MainFsm const&);


    private:
        static MainFsm* instance;

        TestScreen testScreen;
};


#endif