#include <Arduino.h>
#include <SoftTimers.h>

// También hay que poner estos dos defines en ImprovedKeylayouts.h
#define HID_CUSTOM_LAYOUT
#define LAYOUT_SPANISH

#include <HID-Project.h>
#include "CustomKeys.h"


enum States {
  WAITING_FRAME,
  WAITING_TYPE,
  WAITING_LENGTH,
  WAITING_PAYLOAD
};

States state = WAITING_FRAME;
SoftTimer stateTimer;
uint8_t frameType;
uint16_t frameLength;
uint16_t received;

void rxHandler();

uint8_t rxBuffer[1500];


void setup() {
  Consumer.begin();
  Keyboard.begin();
  //Serial.begin(115200);

  TX_RX_LED_INIT;
  RXLED0;
  TXLED1;

  Serial1.begin(115200);
}

void loop() {
  rxHandler();
}


void rxHandler () {
  switch(state) {
    case WAITING_FRAME:

      if (Serial1.available() > 0) {
        uint8_t b = Serial1.read();
        //Serial.println("Received");

        if (b == '%') {
          //Serial.println("frame init");
          state = WAITING_TYPE;
        }
      }
      break;


    case WAITING_TYPE:

      if (Serial1.available() > 0) {
        uint8_t b = Serial1.read();

        if (b == '1' || b == '2' || b == '3') {
          //Serial.print("Frame type: ");
          //Serial.println((char)b);
          frameType = b;
          state = WAITING_LENGTH;
        }
      }
      break;


    case WAITING_LENGTH:

      if (Serial1.available() >= 2) {
        uint8_t b = Serial1.read();
        frameLength = (b << 8) & 0xff00;
        b = Serial1.read();
        frameLength = b & 0x00ff;

        received = 0;
        if (frameLength > 0) {
          //Serial.print("Frame length: ");
          //Serial.println(frameLength);
          state = WAITING_PAYLOAD;
        }
        else {
          //Serial.println("No length");
          state = WAITING_FRAME;
        }
      }
      break;


    case WAITING_PAYLOAD:
      if (Serial1.available() > 0) {
        uint8_t b = Serial1.read();

        if (received < frameLength) {
          received ++;

          if (frameType == '1' || frameType == '2' || frameType == '3') 
            rxBuffer[received - 1] = b;
          

          if (received >= frameLength) {
            if (frameType == '1') {
              for (uint32_t i = 0; i < frameLength; i++) {
                //Serial.print("Payload: ");
                //Serial.println((char)rxBuffer[i]);
                Keyboard.print((char)rxBuffer[i]);
              }
            }
            else if (frameType == '2') {
              
              for (uint32_t i = 0; i < frameLength; i++) {
                //Serial.print("Payload: ");
                //Serial.println((char)rxBuffer[i]);
                
                if (rxBuffer[i] >= 4 && rxBuffer[i] < 0x70)
                  Keyboard.write(static_cast<KeyboardKeycode>(customKeysToKeyCode[rxBuffer[i]]));
                else if (rxBuffer[i] >= 0x70 && rxBuffer[i] < 0x80)
                  Keyboard.press(static_cast<KeyboardKeycode>(customKeysToKeyCode[rxBuffer[i]]));
                else if (rxBuffer[i] >= 0x80) 
                  Consumer.write(static_cast<ConsumerKeycode>(customKeysToKeyCode[rxBuffer[i]]));
              }
              
             /*
              Keyboard.press(KEY_LEFT_CTRL);
              Keyboard.press(KEY_LEFT_SHIFT);
              Keyboard.press(KEY_LEFT_ALT);
              Keyboard.write(KEY_S);
              */
              Keyboard.releaseAll();
            }
            else if (frameType == '3') {
              
              for (uint32_t i = 0; i < frameLength; i++) {
                //Serial.print("Payload: ");
                //Serial.println((char)rxBuffer[i]);

                if (rxBuffer[i] == 0)
                  Keyboard.releaseAll();
                else if (rxBuffer[i] >= 4 && rxBuffer[i] < 0x70)
                  Keyboard.write(static_cast<KeyboardKeycode>(customKeysToKeyCode[rxBuffer[i]]));
                else if (rxBuffer[i] >= 0x70 && rxBuffer[i] < 0x80) 
                  Keyboard.press(static_cast<KeyboardKeycode>(customKeysToKeyCode[rxBuffer[i]]));
                else if (rxBuffer[i] >= 0x80) 
                  Consumer.write(static_cast<ConsumerKeycode>(customKeysToKeyCode[rxBuffer[i]]));
              }
              
              Keyboard.releaseAll();
            }

            state = WAITING_FRAME;
          }
        }
        else
          state = WAITING_FRAME;
      }
      break;
  }
}