#include "../include/SerialLayer.h"


SerialLayer* SerialLayer::instance = nullptr;


SerialLayer* SerialLayer::getInstance() {
    if (instance == nullptr)
        instance = new SerialLayer();

    return instance;
}


SerialLayer::SerialLayer () {
    sendingFrame = false;
    serial = nullptr;
    sendString = false;
    sendArray = false;
    sendMacro = false;
}


void SerialLayer::begin (HardwareSerial* serial) {
    this->serial = serial;
}


void SerialLayer::handler () {
    uint32_t payloadSize = 0;

    if (sendString) {
        payloadSize = strlen(stringToSend);

        serial->print('%');
        serial->print('1');
        serial->write((payloadSize & 0xff00) >> 8);
        serial->write(payloadSize & 0x00ff);

        serial->print(stringToSend);

        sendString = false;
        sendingFrame = false;
    }
    else if (sendArray) {
        payloadSize = keysArrayToSend.size();

        serial->print('%');
        serial->print('2');
        serial->write((payloadSize & 0xff00) >> 8);
        serial->write(payloadSize & 0x00ff);

        for (uint32_t i = 0 ; i < payloadSize; i++) {
            serial->write(keysArrayToSend[i].as<uint32_t>());
        }

        sendArray = false;
        sendingFrame = false;
    }
    else if (sendMacro) {
        payloadSize = keysArrayToSend.size();

        serial->print('%');
        serial->print('3');
        serial->write((payloadSize & 0xff00) >> 8);
        serial->write(payloadSize & 0x00ff);

        for (uint32_t i = 0 ; i < payloadSize; i++) {
            serial->write(keysArrayToSend[i].as<uint32_t>());
        }

        sendMacro = false;
        sendingFrame = false;
    }
}


bool SerialLayer::isSendingFrame () {
    return sendingFrame;
}


void SerialLayer::sendStringFrame (const char* stringToSend) {
    if (!sendingFrame) {
        sendingFrame = true;

        this->stringToSend = stringToSend;

        sendString = true;
    }
}


void SerialLayer::sendKeysFrame (const JsonArray keysArrayToSend) {
    if (!sendingFrame) {
        sendingFrame = true;

        this->keysArrayToSend = keysArrayToSend;

        sendArray = true;
    }
}


void SerialLayer::sendMacroFrame (const JsonArray keysArrayToSend) {
    if (!sendingFrame) {
        sendingFrame = true;

        this->keysArrayToSend = keysArrayToSend;

        sendMacro = true;
    }
}