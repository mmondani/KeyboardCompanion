#include "../../include/Screens/LoadingDataScreen.h"



LoadingDataScreen::LoadingDataScreen()
    : Screen(widgetList, 2),
    background (0, 0, 240, 320, 0xcccccc),
    label1(0, 0, 240, 320, 2, "Cargando Datos", Widget::TextHAlign::CENTER, 0x555555, true, 0xffffff, true) {


    widgetList[0] = &background;
    widgetList[1] = &label1;
}