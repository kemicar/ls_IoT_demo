#include <led.h>

Led::Led(byte pin){
this->pin=pin;
}
void Led::init(){
    pinMode(pin,OUTPUT);
}
void Led::on(){
    digitalWrite(pin,1);
}
void Led::off(){
    digitalWrite(pin,0);
}