
#include <PinChangeInterrupt.h>



/* Motor driver and speed count sensor pin*/
#define LEFT_SPEED_PIN 3
#define RIGHT_SPEED_PIN 2
#define PWMA_PIN 4
#define AIN2_PIN 5
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

volatile byte burp=0;    // a counter to see how many times the pin has changed
volatile byte last_burp = 0;
byte cmd=0;     // a place to put our serial data

byte state = MOVING;

void setup() {
   // set pin to input with a pullup, led to output
  Serial.begin(9600);
  initTouchSensor();
}

void loop() {
  
    switch(state){
      case MOVING:
        processMove();
        break;
      case TURNING:
        processTurn();
        break;
      case STOPED:
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

bools isApproachBarrier(){
  return true;
}

