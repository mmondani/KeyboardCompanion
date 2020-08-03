#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <Adafruit_STMPE610.h>
#include "../include/GUI/Widgets.h"
#include "../include/GUI/GuiHandler.h"


#define CS_TOUCH  21
#define CS_SD     4


TFT_eSPI tft = TFT_eSPI(); 
Adafruit_STMPE610 touch = Adafruit_STMPE610(CS_TOUCH);


GuiHandler* guiHandler;


void setup() {
  Serial.begin(115200);

  tft.init();

  if (! touch.begin()) {
    Serial.println("STMPE not found!");
    while(1);
  }

  guiHandler = GuiHandler::getInstance();
  guiHandler->begin(&tft, &touch, 0, tft.width(), tft.height());

}

void loop() {
  guiHandler->handler();
}