#include "../../include/Screens/TestScreen.h"



TestScreen::TestScreen(FSProvider* fsProvider)
    : Screen(widgetList, 6),
    background (0, 0, 240, 320, 0xcccccc),
    rect1(10, 10, 100, 50, 0xff0000, true, 0x00ff00),
    rect2(50, 100, 50, 100, 0x00ff00, true, 0x0000ff),
    label1(20, 250, 200, 30, 2, "Hola mundo", Widget::TextHAlign::CENTER, 0x555555, true, 0x00dddd, true),
    button1(150, 100, 80, 100, 2, "Click", Widget::TextHAlign::CENTER, 0x555555, true, 0x00dddd, true),
    iconButton1(150, 10, 70, 70, fsProvider, "1.jpg") {

    widgetList[0] = &background;
    widgetList[1] = &rect1;
    widgetList[2] = &rect2;
    widgetList[3] = &label1;
    widgetList[4] = &button1;
    widgetList[5] = &iconButton1;

    rect1.setClickable(true);
    rect2.setVisible(false);
    label1.setClickable(true);


    Widget::connect(rect1.click, [this](void) {
        this->rect2.setVisible(true);
    });

    Widget::connect(rect1.release, [this](void) {
        this->rect2.setVisible(false);
    });

    Widget::connect(label1.click, [this](void) {
        this->label1.setText("Click");
        this->label1.setTextHAlign(Widget::TextHAlign::RIGHT);
        this->label1.setTextSize(1);
        this->label1.show();
    });

    Widget::connect(label1.release, [this](void) {
        this->label1.setText("Hola mundo");
        this->label1.setTextHAlign(Widget::TextHAlign::CENTER);
        this->label1.setTextSize(2);
        this->label1.show();
    });
}