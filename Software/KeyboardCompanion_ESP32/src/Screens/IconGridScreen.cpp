#include "../../include/Screens/IconGridScreen.h"


#define ICON_WIDTH      70
#define ICON_HEIGHT     ICON_WIDTH
#define GRID_OFFSET_X   0
#define GRID_OFFSET_Y   50
#define CELL_WIDTH      80
#define CELL_HEIGHT     90
#define CELL_PADDING_X  5
#define CELL_PADDING_Y  10

IconGridScreen::IconGridScreen(FSProvider* fsProvider)
    : Screen(widgetList, 10),
    background (0, 0, 240, 320, 0xcccccc),
    iconButton0(GRID_OFFSET_X + 0 * CELL_WIDTH + CELL_PADDING_X, GRID_OFFSET_Y + 0 * CELL_HEIGHT + CELL_PADDING_Y, ICON_WIDTH, ICON_HEIGHT, fsProvider, "9.jpg"),
    iconButton1(GRID_OFFSET_X + 1 * CELL_WIDTH + CELL_PADDING_X, GRID_OFFSET_Y + 0 * CELL_HEIGHT + CELL_PADDING_Y, ICON_WIDTH, ICON_HEIGHT, fsProvider, "9.jpg"),
    iconButton2(GRID_OFFSET_X + 2 * CELL_WIDTH + CELL_PADDING_X, GRID_OFFSET_Y + 0 * CELL_HEIGHT + CELL_PADDING_Y, ICON_WIDTH, ICON_HEIGHT, fsProvider, "9.jpg"),
    iconButton3(GRID_OFFSET_X + 0 * CELL_WIDTH + CELL_PADDING_X, GRID_OFFSET_Y + 1 * CELL_HEIGHT + CELL_PADDING_Y, ICON_WIDTH, ICON_HEIGHT, fsProvider, "9.jpg"),
    iconButton4(GRID_OFFSET_X + 1 * CELL_WIDTH + CELL_PADDING_X, GRID_OFFSET_Y + 1 * CELL_HEIGHT + CELL_PADDING_Y, ICON_WIDTH, ICON_HEIGHT, fsProvider, "9.jpg"),
    iconButton5(GRID_OFFSET_X + 2 * CELL_WIDTH + CELL_PADDING_X, GRID_OFFSET_Y + 1 * CELL_HEIGHT + CELL_PADDING_Y, ICON_WIDTH, ICON_HEIGHT, fsProvider, "9.jpg"),
    iconButton6(GRID_OFFSET_X + 0 * CELL_WIDTH + CELL_PADDING_X, GRID_OFFSET_Y + 2 * CELL_HEIGHT + CELL_PADDING_Y, ICON_WIDTH, ICON_HEIGHT, fsProvider, "9.jpg"),
    iconButton7(GRID_OFFSET_X + 1 * CELL_WIDTH + CELL_PADDING_X, GRID_OFFSET_Y + 2 * CELL_HEIGHT + CELL_PADDING_Y, ICON_WIDTH, ICON_HEIGHT, fsProvider, "9.jpg"),
    iconButton8(GRID_OFFSET_X + 2 * CELL_WIDTH + CELL_PADDING_X, GRID_OFFSET_Y + 2 * CELL_HEIGHT + CELL_PADDING_Y, ICON_WIDTH, ICON_HEIGHT, fsProvider, "9.jpg") {


    iconClickCallback = nullptr;


    widgetList[0] = &background;
    widgetList[1] = &iconButton0;
    widgetList[2] = &iconButton1;
    widgetList[3] = &iconButton2;
    widgetList[4] = &iconButton3;
    widgetList[5] = &iconButton4;
    widgetList[6] = &iconButton5;
    widgetList[7] = &iconButton6;
    widgetList[8] = &iconButton7;
    widgetList[9] = &iconButton8;


    Widget::connect(iconButton0.release, [this](Widget* widget) {
        if (iconClickCallback != nullptr)
            iconClickCallback(0);
    });

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
}


void IconGridScreen::setIcon (uint32_t iconNumber, const char* fileName) {
    if (iconNumber >= 0 && iconNumber <= 8) {
        ((IconButton*)(widgetList[1 + iconNumber]))->setFileName(fileName);
    }
}


void IconGridScreen::setIconClickCallback (IconGridScreenCallbacks::IconClick callback) {
    iconClickCallback = callback;
}


void IconGridScreen::setNavigationEventCallback (IconGridScreenCallbacks::NavigationClick callback) {
    navigationEventCallback = callback;
}