#ifndef WIDGET_H
#define WIDGET_H

#include <functional>
#include <TFT_eSPI.h>
#include "../RingBuffer.h"


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
        enum WidgetEventType {
            DRAW,
            HIDE
        };

        typedef struct {
            Widget* widget;
            WidgetEventType type;
        } WidgetEvent;


        Widget(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
        static void setWidgetEventBuffer(RingBuffer<WidgetEvent>* buffer);
        const uint32_t& getX () const { return x; };
        const uint32_t& getY () const { return y; };
        const uint32_t& getW () const { return w; };
        const uint32_t& getH () const { return h; };
        const bool& getVisible () const { return visible; };
        void setX (const uint32_t& x) { this->x = x; };
        void setY (const uint32_t& y) { this->y = y; };
        void setW (const uint32_t& w) { this->w = w; };
        void setH (const uint32_t& h) { this->h = h; };
        void setVisible (const bool& v);
        bool containsPoint (uint32_t x, uint32_t y);
        void show ();
        void hide ();
        static void connect (WidgetSignal& signal, SignalSlot slot);
        void emit (WidgetSignal& signal);
        virtual void draw(TFT_eSPI* tft) = 0;
        virtual void clearArea(TFT_eSPI* tft) = 0;
        virtual void onClick() = 0;
        virtual void onRelease()  = 0;


    protected:
        static RingBuffer<WidgetEvent>* widgetEventBuffer;
        uint32_t x;
        uint32_t y;
        uint32_t w; 
        uint32_t h;
        bool visible;

    private:
};



#endif