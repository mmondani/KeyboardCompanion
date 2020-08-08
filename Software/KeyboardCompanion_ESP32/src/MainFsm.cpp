#include "../include/MainFsm.h"


MainFsm* MainFsm::instance = nullptr;


MainFsm* MainFsm::getInstance() {
    if (instance == nullptr)
        instance = new MainFsm();
    
    return instance;
}


MainFsm::MainFsm() 
      : testScreen(FSProvider::getInstance()) {
}


void MainFsm::begin () {
    GuiHandler::getInstance()->setScreen(&testScreen);

    testScreen.setIconClickCallback([this](void) {
        GuiHandler::getInstance()->setScreen(&testScreen);
    });
}


void MainFsm::handler () {

}