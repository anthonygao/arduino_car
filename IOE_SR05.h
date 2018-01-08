#include "Timer.h"

#ifndef IOE_SR05_H
#define IOE_SR05_H
/*
    IOE-SR05 have 5 pins, VCC, TRIG, ECHO, GND, GND. This ultrasonic sensor uses Arduino RX to report distance data. Every 18ms it sends wave and count
    reflect if TRIG pin is LOW which means TRIG pin is connected to GND. 
    Every detected data has 4 bytes, first byte is 0xff, sencond and third byte are distance data with mearsue "mm". Last byte
    is check byte with summary.
*/
class IOE_SR05:public TimerCall{
    public:
        Timer t;
        int distance = 0;
        int last_distance = 0;
    private:
        unsigned char head,dh,dl,sum;
    
    public:
        void initialize(int rate);
        void timer_callback();
        void update();
        int get_distance_cm();
        int get_distance_mm();

        void print_debug_info();
};


#endif

