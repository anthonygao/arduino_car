//
// Created by Gao An Dong on 2017/12/25.
//

#ifndef MYCAR_MOTOR_H
#define MYCAR_MOTOR_H

#include <Arduino.h>
#include "constant_define.h"

#define FORWARD 0
#define LEFT_TURN 1
#define RIGHT_TURN 2
#define BACK 4

#define FULL_SPEED 255
#define MOVE_FORWARD true
#define MOVE_BACKWARD false

byte move_state = FORWARD;

int left_speed = FULL_SPEED;
int right_speed = FULL_SPEED;

volatile int left_count = 0;
volatile int right_count = 0;

void sum_left_wheel();
void sum_right_wheel();
void left_move(bool direction,int speed);
void right_move(bool direction,int speed);

void initMotor(){
    pinMode(AIN2_PIN,OUTPUT);
    pinMode(AIN1_PIN,OUTPUT);
    pinMode(BIN1_PIN,OUTPUT);
    pinMode(BIN2_PIN,OUTPUT);
    pinMode(STBY_PIN,OUTPUT);
    pinMode(PWMA_PIN,OUTPUT);
    pinMode(PWMB_PIN,OUTPUT);

    attachInterrupt(LEFT_SPEED_PIN,sum_left_wheel,RISING);
    attachInterrupt(RIGHT_SPEED_PIN,sum_right_wheel,RISING);

    digitalWrite(STBY_PIN,HIGH);
    left_move(FORWARD,left_speed);
    right_move(FORWARD,right_speed);

}

void left_move(bool direction,int speed){
    if(direction){
        digitalWrite(AIN1_PIN,HIGH);
        digitalWrite(AIN2_PIN,LOW);
    }else{
        digitalWrite(AIN1_PIN,LOW);
        digitalWrite(AIN2_PIN,HIGH);
    }
    left_speed = speed*FULL_SPEED;
    digitalWrite(PWMA_PIN,left_speed);

}

void keep_straight(){
    int deviation = left_speed - right_speed;
    if(deviation > 5){
        left_speed *= 0.98;
        right_speed *= 1.02;
        right_speed = right_speed > 100?100:right_speed;
    }
    if(deviation < -5){
        left_speed *= 1.02;
        right_speed *= 0.98;
        left_speed = left_speed > 100?100:left_speed;
    }

}

void right_move(bool direction,int speed){
    if(direction){
        digitalWrite(BIN1_PIN,HIGH);
        digitalWrite(BIN2_PIN,LOW);
    }else{
        digitalWrite(BIN1_PIN,LOW);
        digitalWrite(BIN2_PIN,HIGH);
    }
    right_speed = speed*FULL_SPEED;
    digitalWrite(PWMB_PIN,right_speed);
}

void stop_motor(){
    digitalWrite(STBY_PIN,LOW);
    digitalWrite(AIN1_PIN,LOW);
    digitalWrite(AIN2_PIN,LOW);
    digitalWrite(BIN1_PIN,LOW);
    digitalWrite(BIN2_PIN,LOW);
    digitalWrite(PWMA_PIN,0);
    digitalWrite(PWMB_PIN,0);

}

void move_backward(){
  keep_straight();
  left_move(MOVE_BACKWARD,left_speed);
  right_move(MOVE_BACKWARD,right_speed);
}

void move_forward(){
  keep_straight();
  left_move(MOVE_FORWARD,FULL_SPEED);
  right_move(MOVE_FORWARD,FULL_SPEED);
}

bool is_back_done(){
  if(left_count >40 || right_count > 40){
    return true;
  }
  return false;
}

void clear_state(){
  left_count = 0;
  right_count = 0;
  digitalWrite(STBY_PIN,HIGH);
}

void rotation(bool clock_direction){
  if(clock_direction){
     left_move(MOVE_FORWARD,FULL_SPEED);
     right_move(MOVE_BACKWARD,FULL_SPEED);
  }else{
     left_move(MOVE_BACKWARD,FULL_SPEED);
     right_move(MOVE_FORWARD,FULL_SPEED);
  }
}

bool is_rotate_done(int degree){
  if(left_count + right_count >= degree){
    return true;
  }
  return false;
}
void sum_left_wheel(){
    left_count++;
    if(move_state == FORWARD && left_count > 6000){
        left_count = 0;
        right_speed = 0;
    }
}
void sum_right_wheel(){
    right_count++;
    if(move_state == FORWARD && right_count > 6000){
        left_count = 0;
        right_speed = 0;
    }
}
#endif //MYCAR_MOTOR_H
