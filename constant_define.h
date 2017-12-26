//
// Created by Gao An Dong on 2017/12/25.
//

#ifndef ARDUINOTEMPLATE_PIN_DEFINE_H
#define ARDUINOTEMPLATE_PIN_DEFINE_H

/* Motor driver and speed count sensor pin*/
#define LEFT_SPEED_PIN 1 // PIN 3 
#define RIGHT_SPEED_PIN 0 // PIN 2
#define PWMA_PIN 5
#define AIN2_PIN 4
#define AIN1_PIN 6
#define STBY_PIN 7
#define BIN1_PIN 8
#define BIN2_PIN 9
#define PWMB_PIN 10
/* ultra distance sensor pin*/
#define TRIG_PIN 11
#define ECHO_PIN 12

/* collapse sensor 3 in 1 */
#define TOUCH_PIN 13

/* Car state */
#define MOVING 0
#define TURNING 1
#define STOPPED 2
#define BACKING 3
#define MIDDLE_STATE 4

#endif //ARDUINOTEMPLATE_PIN_DEFINE_H
