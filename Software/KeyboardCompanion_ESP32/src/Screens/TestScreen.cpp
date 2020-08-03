#include "../../include/Screens/TestScreen.h"



TestScreen::TestScreen()
    : rect1(10, 10, 100, 50, 0xff0000, true, 0x00ff00),
    rect2(50, 100, 50, 100, 0x00ff00, true, 0x0000ff) {

}


void TestScreen::show() {
    rect1.show();
    rect2.show();
}

void TestScreen::hide() {
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