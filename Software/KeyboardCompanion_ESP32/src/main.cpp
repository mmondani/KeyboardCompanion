#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <Adafruit_STMPE610.h>
#include "../include/GUI/Widgets.h"



TFT_eSPI tft = TFT_eSPI(); 

Rectangle rect = Rectangle(&tft, 10, 10, 100, 50, 0xff0000, true, 0x00ff00);


void setup() {
  Widget* widget = &rect;
  Serial.begin(115200);

  tft.init();
  tft.setRotation(0);
  tft.fillScreen(Color::toTftColor(0xffffff));

  widget->draw();
}

void loop() {

}