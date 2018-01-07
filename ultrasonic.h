#include "Timer.h"

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

Timer t;
int distance = 0;
int last_distance = 0;
unsigned char head,dh,dl,sum;

void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
  Serial.println("Begin");
  t.every(50, takeReading);
}

void loop() {
  t.update();
  print_sonar();
}
void takeReading(){
   while(Serial.available()>0){
        head = Serial.read();
        if (head != 0xff) continue;
        dh = Serial.read();
        dl = Serial.read();
        sum = Serial.read();
        head = head + dh + dl;

        if (head != sum) continue;  //和校验错
        last_distance = distance;
        distance = (dh*256 + dl)/10; // distance is in "mm", convert to "cm"
        Serial.flush();
   }
}
void print_sonar(){
    if(last_distance != distance && distance > 0){
        Serial.print("Ping: ");
        Serial.print(distance); 
        Serial.println("cm");
    }
 
}

#endif

