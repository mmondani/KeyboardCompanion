#ifndef WIDGET_H
#define WIDGET_H

#include <functional>
#include <TFT_eSPI.h>


typedef std::function<void(void)> SignalSlot;

class WidgetSignal {
    public:
        WidgetSignal();
        WidgetSignal(SignalSlot slot);
        void add(SignalSlot slot);
        WidgetSignal* getNext();
        SignalSlot getSlot();

    private:
        WidgetSignal* next;
        SignalSlot slot;
};



class Widget {
    public:
        Widget(TFT_eSPI* tft, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
        uint32_t getX ();
        uint32_t getY ();
        uint32_t getW ();
        uint32_t getH ();
        void setX (uint32_t x);
        void setY (uint32_t y);
        void setW (uint32_t w);
        void setH (uint32_t h);
        bool containsPoint (uint32_t x, uint32_t y);
        static void connect (WidgetSignal signal, SignalSlot slot);
        void emmit (WidgetSignal signal);
        virtual void draw() = 0;
        virtual void clearArea() = 0;
        virtual void onClick() = 0;
        virtual void onRelease()  = 0;


    protected:
        TFT_eSPI* tft;
        uint32_t x;
        uint32_t y;
        uint32_t w; 
        uint32_t h;

    private:
};



#endif