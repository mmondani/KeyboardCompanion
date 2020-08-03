#include "../../include/Screens/TestScreen.h"



TestScreen::TestScreen()
    : background (0, 0, 240, 320, 0xcccccc),
    rect1(10, 10, 100, 50, 0xff0000, true, 0x00ff00),
    rect2(50, 100, 50, 100, 0x00ff00, true, 0x0000ff) {

    rect1.setClickable(true);
    rect2.setVisible(false);


    Widget::connect(rect1.click, [this](void) {
        this->rect2.setVisible(true);
    });

    Widget::connect(rect1.release, [this](void) {
        this->rect2.setVisible(false);
    });
}


void TestScreen::show() {
    background.show();
    rect1.show();
    rect2.show();
}

void TestScreen::hide() {
    background.hide();
    rect1.hide();
    rect2.hide();
}


void TestScreen::onClick(uint32_t x, uint32_t y) {
    if (rect1.containsPoint(x, y))
        rect1.onClick();
    if (rect2.containsPoint(x, y))
        rect2.onClick();
}


void TestScreen::onRelease(uint32_t x, uint32_t y) {
    if(rect1.containsPoint(x, y))
        rect1.onRelease();
    if (rect2.containsPoint(x, y))
        rect2.onRelease();
}