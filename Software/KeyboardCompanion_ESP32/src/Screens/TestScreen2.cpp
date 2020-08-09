#include "../../include/Screens/TestScreen2.h"


#define ICON_WIDTH      70
#define ICON_HEIGHT     ICON_WIDTH
#define GRID_OFFSET_X   0
#define GRID_OFFSET_Y   50
#define CELL_WIDTH      80
#define CELL_HEIGHT     90
#define CELL_PADDING_X  5
#define CELL_PADDING_Y  10

TestScreen2::TestScreen2(FSProvider* fsProvider)
    : Screen(widgetList, 10),
    background (0, 0, 240, 320, 0xcccccc),
    iconButton1(GRID_OFFSET_X + 0 * CELL_WIDTH + CELL_PADDING_X, GRID_OFFSET_Y + 0 * CELL_HEIGHT + CELL_PADDING_Y, ICON_WIDTH, ICON_HEIGHT, fsProvider, "1.jpg"),
    iconButton2(GRID_OFFSET_X + 1 * CELL_WIDTH + CELL_PADDING_X, GRID_OFFSET_Y + 0 * CELL_HEIGHT + CELL_PADDING_Y, ICON_WIDTH, ICON_HEIGHT, fsProvider, "2.jpg"),
    iconButton3(GRID_OFFSET_X + 2 * CELL_WIDTH + CELL_PADDING_X, GRID_OFFSET_Y + 0 * CELL_HEIGHT + CELL_PADDING_Y, ICON_WIDTH, ICON_HEIGHT, fsProvider, "3.jpg"),
    iconButton4(GRID_OFFSET_X + 0 * CELL_WIDTH + CELL_PADDING_X, GRID_OFFSET_Y + 1 * CELL_HEIGHT + CELL_PADDING_Y, ICON_WIDTH, ICON_HEIGHT, fsProvider, "4.jpg"),
    iconButton5(GRID_OFFSET_X + 1 * CELL_WIDTH + CELL_PADDING_X, GRID_OFFSET_Y + 1 * CELL_HEIGHT + CELL_PADDING_Y, ICON_WIDTH, ICON_HEIGHT, fsProvider, "5.jpg"),
    iconButton6(GRID_OFFSET_X + 2 * CELL_WIDTH + CELL_PADDING_X, GRID_OFFSET_Y + 1 * CELL_HEIGHT + CELL_PADDING_Y, ICON_WIDTH, ICON_HEIGHT, fsProvider, "6.jpg"),
    iconButton7(GRID_OFFSET_X + 0 * CELL_WIDTH + CELL_PADDING_X, GRID_OFFSET_Y + 2 * CELL_HEIGHT + CELL_PADDING_Y, ICON_WIDTH, ICON_HEIGHT, fsProvider, "7.jpg"),
    iconButton8(GRID_OFFSET_X + 1 * CELL_WIDTH + CELL_PADDING_X, GRID_OFFSET_Y + 2 * CELL_HEIGHT + CELL_PADDING_Y, ICON_WIDTH, ICON_HEIGHT, fsProvider, "8.jpg"),
    iconButton9(GRID_OFFSET_X + 2 * CELL_WIDTH + CELL_PADDING_X, GRID_OFFSET_Y + 2 * CELL_HEIGHT + CELL_PADDING_Y, ICON_WIDTH, ICON_HEIGHT, fsProvider, "9.jpg") {


    iconClickCallback = nullptr;


    widgetList[0] = &background;
    widgetList[1] = &iconButton1;
    widgetList[2] = &iconButton2;
    widgetList[3] = &iconButton3;
    widgetList[4] = &iconButton4;
    widgetList[5] = &iconButton5;
    widgetList[6] = &iconButton6;
    widgetList[7] = &iconButton7;
    widgetList[8] = &iconButton8;
    widgetList[9] = &iconButton9;


    Widget::connect(iconButton1.release, [this](Widget* widget) {
        if (iconClickCallback != nullptr)
            iconClickCallback(1);
    });

    Widget::connect(iconButton2.release, [this](Widget* widget) {
        if (iconClickCallback != nullptr)
            iconClickCallback(2);
    });

    Widget::connect(iconButton3.release, [this](Widget* widget) {
        if (iconClickCallback != nullptr)
            iconClickCallback(3);
    });

    Widget::connect(iconButton4.release, [this](Widget* widget) {
        if (iconClickCallback != nullptr)
            iconClickCallback(4);
    });

    Widget::connect(iconButton5.release, [this](Widget* widget) {
        if (iconClickCallback != nullptr)
            iconClickCallback(5);
    });

    Widget::connect(iconButton6.release, [this](Widget* widget) {
        if (iconClickCallback != nullptr)
            iconClickCallback(6);
    });

    Widget::connect(iconButton7.release, [this](Widget* widget) {
        if (iconClickCallback != nullptr)
            iconClickCallback(7);
    });

    Widget::connect(iconButton8.release, [this](Widget* widget) {
        if (iconClickCallback != nullptr)
            iconClickCallback(8);
    });

    Widget::connect(iconButton9.release, [this](Widget* widget) {
        if (iconClickCallback != nullptr)
            iconClickCallback(9);
    });
}


void TestScreen2::setIconClickCallback (TestScreen2Callbacks::IconClick callback) {
    iconClickCallback = callback;
}