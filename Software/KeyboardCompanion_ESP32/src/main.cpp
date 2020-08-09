#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <FS.h>
#include <SD.h>
#include <Adafruit_STMPE610.h>
#include "../include/GUI/GuiHandler.h"
#include "MainFsm.h"


#define CS_TOUCH  21
#define CS_SD     4


TFT_eSPI tft = TFT_eSPI(); 
Adafruit_STMPE610 touch = Adafruit_STMPE610(CS_TOUCH);

GuiHandler* guiHandler;
MainFsm* mainFsm;


void setup() {
  Serial.begin(115200);

  tft.init();

  if (! touch.begin()) {
    Serial.println("STMPE not found!");
    while(1);
  }

  if (!SD.begin(CS_SD)) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  FSProvider::getInstance()->begin(&SD);

  guiHandler = GuiHandler::getInstance();
  guiHandler->begin(&tft, &touch, 1, tft.width(), tft.height());

  mainFsm = MainFsm::getInstance();
  mainFsm->begin();
}

void loop() {
  guiHandler->handler();
  mainFsm->handler();
}