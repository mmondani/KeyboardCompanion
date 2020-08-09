#include "../include/MainFsm.h"


MainFsm* MainFsm::instance = nullptr;


MainFsm* MainFsm::getInstance() {
    if (instance == nullptr)
        instance = new MainFsm();
    
    return instance;
}


MainFsm::MainFsm() 
      : testScreen(FSProvider::getInstance()),
      testScreen2(FSProvider::getInstance()) {
}


void MainFsm::begin () {
    GuiHandler::getInstance()->setScreen(&testScreen);

    testScreen.setIconClickCallback([this](void) {
        GuiHandler::getInstance()->setScreen(&testScreen2);
    });

    testScreen2.setIconClickCallback([this](uint32_t iconNumber) {
        if (iconNumber != 9) {
            Serial.print("Icono: ");
            Serial.println(iconNumber);
        }
        else {
            GuiHandler::getInstance()->setScreen(&testScreen);
        }
    });
}


void MainFsm::handler () {

}