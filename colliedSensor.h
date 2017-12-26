//
// Created by Gao An Dong on 2017/12/25.
//

#ifndef ARDUINOTEMPLATE_COLLIEDSENSOR_H
#define ARDUINOTEMPLATE_COLLIEDSENSOR_H

#include "constant_define.h"
#include <Arduino.h>
#include <PinChangeInterrupt.h>


volatile byte burp=0;    // a counter to see how many times the pin has changed
volatile byte last_burp = 0;
void burpcount();

void initTouchSensor(){
    pinMode(TOUCH_PIN, INPUT_PULLUP);
    attachPCINT(digitalPinToPCINT(TOUCH_PIN), burpcount, FALLING);

}

void burpcount()
{
    burp++;
}

bool isCollide(){
    if(burp > last_burp){
        burp = 0;
        last_burp =0;
        return true;
    }
    return false;
}

bool isApproachBarrier(){
    return true;
}

#endif //ARDUINOTEMPLATE_COLLIEDSENSOR_H
