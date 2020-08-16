#ifndef SERIALLAYER_H
#define SERIALLAYER_H

#include <HardwareSerial.h>
#include <ArduinoJson.h>


class SerialLayer {
    public:
        static SerialLayer* getInstance();
        void begin (HardwareSerial* serial);
        void handler ();
        bool isSendingFrame ();
        void sendStringFrame (const char* stringToSend);
        void sendKeysFrame (const JsonArray keysArrayToSend);
        void sendMacroFrame (const JsonArray keysArrayToSend);


    protected:
        SerialLayer();
        SerialLayer (SerialLayer const&);
        SerialLayer& operator= (SerialLayer const&);


    private:
        static SerialLayer* instance;
        HardwareSerial* serial;
        bool sendingFrame;
        const char* stringToSend;
        JsonArray keysArrayToSend;
        bool sendString;
        bool sendArray;
        bool sendMacro;
};


#endif