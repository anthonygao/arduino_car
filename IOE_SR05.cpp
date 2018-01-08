#include "IOE_SR05.h"

void IOE_SR05::initialize(int rate,int period){
    if(rate < 0){
        return;
    }
    Serial.begin(rate);
    t.every(period,this);
}

void IOE_SR05::timer_callback(){
    while(Serial.available()>0){
        head = Serial.read();
        if (head != 0xff) continue;
        dh = Serial.read();
        dl = Serial.read();
        sum = Serial.read();
        head = head + dh + dl;

        if (head != sum) continue;  //和校验错
        last_distance = distance;
        distance = dh*256 + dl; // distance is in "mm"
        Serial.flush();
   }
}

void IOE_SR05::update(){
    t.update();
}

int IOE_SR05::get_distance_cm(){
    return distance/10;
}

int IOE_SR05::get_distance_mm(){
    return distance;
}

void IOE_SR05::print_debug_info(){
    Serial.print("Ping: ");
    Serial.print(distance); 
    Serial.println("cm");
}