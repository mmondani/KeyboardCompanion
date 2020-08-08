#include "../../include/GUI/FSProvider.h"


FSProvider* FSProvider::instance = nullptr;



FSProvider* FSProvider::getInstance() {
    if (instance == nullptr)
        instance = new FSProvider();
    
    return instance;
}

FSProvider::FSProvider() {
    mutex = false;
}


void FSProvider::begin(FS* fs) {
    this->fs = fs;
}


fs::FS* FSProvider::take () {
    fs::FS* ret = nullptr;

    if (!mutex) {
        ret = fs;
        mutex = true;
    }

    return ret;
}


void FSProvider::give () {
    mutex = false;
}
