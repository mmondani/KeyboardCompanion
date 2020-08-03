#include "../../include/Screens/TestScreen.h"



TestScreen::TestScreen()
    : Screen(widgetList, 3),
    background (0, 0, 240, 320, 0xcccccc),
    rect1(10, 10, 100, 50, 0xff0000, true, 0x00ff00),
    rect2(50, 100, 50, 100, 0x00ff00, true, 0x0000ff) {

    widgetList[0] = &background;
    widgetList[1] = &rect1;
    widgetList[2] = &rect2;

    rect1.setClickable(true);
    rect2.setVisible(false);


    Widget::connect(rect1.click, [this](void) {
        this->rect2.setVisible(true);
    });

    Widget::connect(rect1.release, [this](void) {
        this->rect2.setVisible(false);
    });
}