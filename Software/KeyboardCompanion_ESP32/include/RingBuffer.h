#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdint.h>

template <class  T>
class RingBuffer {
    public:
        RingBuffer (uint32_t size);
        uint32_t getFreeSpace ();
        uint32_t getPending ();
        T* getFreeSlot ();
        T* remove ();
        void flush ();

    private:
        T* buffer;
        uint32_t size;
        uint32_t ptrIn;
        uint32_t ptrOut;
        uint32_t count;
};



template <class  T>
RingBuffer<T>::RingBuffer (uint32_t size) {
    buffer = new T[size];
    ptrIn = 0;
    ptrOut = 0;
    this->size = size;
    count = 0;
}


template <class  T>
uint32_t RingBuffer<T>::getFreeSpace () {
    return (size - count);
}


template <class  T>
uint32_t RingBuffer<T>::getPending () {
    return count;
}


template <class  T>
T* RingBuffer<T>::getFreeSlot () {
    T* ret = nullptr;

    if (getFreeSpace() > 0) {
        ret = &(buffer[ptrIn]);

        count ++;
        ptrIn ++;
        if (ptrIn >= size)
            ptrIn = 0;
    }

    return ret;
}


template <class  T>
T* RingBuffer<T>::remove () {
    T* ret = nullptr;

    if (getPending() > 0) {
        ret = &(buffer[ptrOut]);

        count --;
        ptrOut ++;
        if (ptrOut >= size)
            ptrOut = 0;
    }

    return ret;
}


template <class  T>
void RingBuffer<T>::flush () {
    ptrIn = 0;
    ptrOut = 0;
    count = 0;
}


#endif