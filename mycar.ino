
#include <PinChangeInterrupt.h>
#include "constant_define.h"
#include "colliedSensor.h"
#include "motor.h"
#include "ultrasensor.h"
#include <Arduino.h>

byte state = MOVING;

int debug_step = 20;
int last_count = 0;

void readyToMove();
void processMove();
void processTurn();
void processBack();
void stopCar();

void setup() {
   // set pin to input with a pullup, led to output
  Serial.begin(9600);
  initTouchSensor();
  initMotor();
}

void loop() {
    if(isCollide() == true){
      state = STOPPED;
    }
    switch(state){
      case MOVING:
        if(is_approach_blocks()){
          state = STOPPED;
          break;
        }
        processMove();
        break;
      case TURNING:
        processTurn();
        break;
      case STOPPED:
        stopCar();
        break;
      case BACKING:
        processBack();
        break;
      case MIDDLE_STATE:
        readyToMove();
        break;
    }


}

void processMove(){
  move_forward();
}

void processTurn(){
  if(is_rotate_done(90)){
    state = FORWARD;
    clear_state();
  }
  rotation(true);
}

void stopCar(){
  state = BACKING;
  stop_motor();
  clear_state();
}

void processBack(){
  if(is_back_done()){
    state = TURNING;
    clear_state();
  }
  move_backward();
}

void readyToMove(){

}

void debugInfo(){
  //if(left_count - last_count > debug_step){
    Serial.print("LEFT:");
    Serial.print(left_count,DEC);
    Serial.println("");

    Serial.print("RIGHT:");
    Serial.print(right_count,DEC);
    Serial.println("");

    Serial.print("STATE:");
    Serial.println(state);
    last_count = left_count;
 // }
  
}

