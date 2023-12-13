#ifndef led_h
#define led_h

#include <Arduino.h>

class Led{
    private:
        byte pin;
    public:
        Led(){};
        Led(byte pin);
        void init();
        void on();
        void off();

    
};


#endif led_h
