#ifndef WIDGET_H
#define WIDGET_H

#include <functional>
#include <TFT_eSPI.h>
#include "../RingBuffer.h"
#include "ProjectColors.h"


class Widget {
    public:
        typedef std::function<void(Widget* widget)> SignalSlot;

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

        enum WidgetEventType {
            DRAW,
            HIDE
        };

        typedef struct {
            Widget* widget;
            WidgetEventType type;
        } WidgetEvent;

        enum TextHAlign {
            LEFT,
            CENTER,
            RIGHT
        };


        Widget(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
        static void setWidgetEventBuffer(RingBuffer<WidgetEvent>* buffer);
        const uint32_t& getX () const { return x; };
        const uint32_t& getY () const { return y; };
        const uint32_t& getW () const { return w; };
        const uint32_t& getH () const { return h; };
        const bool& getVisible () const { return visible; };
        const bool& getClickable () const { return clickable; };
        const bool& getClicked () const { return clicked; };
        void setX (const uint32_t& x) { this->x = x; };
        void setY (const uint32_t& y) { this->y = y; };
        void setW (const uint32_t& w) { this->w = w; };
        void setH (const uint32_t& h) { this->h = h; };
        void setVisible (const bool& v);
        void setClickable (const bool& c) { this->clickable = c; };
        void setClicked (const bool& c) { this->clicked = c; };
        bool containsPoint (uint32_t x, uint32_t y);
        void show ();
        void hide ();
        void onClick();
        void onRelease();
        static void connect (WidgetSignal& signal, SignalSlot slot);
        void emit (WidgetSignal& signal);
        virtual void draw(TFT_eSPI* tft) = 0;
        virtual void clearArea(TFT_eSPI* tft) = 0;

        WidgetSignal click;
        WidgetSignal release;


    protected:
        static RingBuffer<WidgetEvent>* widgetEventBuffer;
        uint32_t x;
        uint32_t y;
        uint32_t w; 
        uint32_t h;
        bool visible;
        bool clickable;
        bool clicked;

    private:
};



#endif