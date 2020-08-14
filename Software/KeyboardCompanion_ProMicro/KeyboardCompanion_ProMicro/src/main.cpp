#include <Arduino.h>
#include <SoftTimers.h>

#define HID_CUSTOM_LAYOUT
#define LAYOUT_SPANISH

#include <HID-Project.h>


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

        if (b == '1' || b == '2') {
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

          if (frameType == '1') {
            rxBuffer[received - 1] = b;
          }
          else if (frameType == '2') {
            
          }

          if (received >= frameLength) {
            if (frameType == '1') {
              for (uint32_t i = 0; i < frameLength; i++) {
                //Serial.print("Payload: ");
                //Serial.println((char)rxBuffer[i]);
                Keyboard.print((char)rxBuffer[i]);
              }
            }
            else if (frameType == '2') {
              
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