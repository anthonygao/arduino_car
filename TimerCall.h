/*
Original Timer library does not support OOP callback. This is an interface for OOP callback; 

*/

#ifndef TIMECALL_H
#define TIMECALL_H

class TimerCall{
    public:
        virtual void timer_callback();
};
#endif