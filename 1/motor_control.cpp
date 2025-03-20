#include "motor_control.h"
#define LRPWM 9
#define LLPWM 10
#define LPWM 11
#define RRPWM 6
#define RLPWM 7
#define RPWM 8
#define sLow 85

void setupMotors() {
 
pinMode(LRPWM, OUTPUT);
pinMode(LLPWM, OUTPUT);
pinMode(LPWM, OUTPUT);
pinMode(RRPWM, OUTPUT);
pinMode(RLPWM, OUTPUT);
pinMode(RPWM, OUTPUT);
     
}

void moveForward() {
  digitalWrite(LRPWM, LOW);
  digitalWrite(LLPWM, HIGH);
  analogWrite(LPWM, sLow);
  digitalWrite(RRPWM, HIGH);
  digitalWrite(RLPWM, LOW);
  analogWrite(RPWM, sLow);
 
}

void moveBackward() {
  digitalWrite(LRPWM, HIGH);
  digitalWrite(LLPWM, LOW);
  analogWrite(LPWM, sLow);
  digitalWrite(RRPWM, HIGH);
  digitalWrite(RLPWM, LOW);
  analogWrite(RPWM, sLow);
 
}

void stopMotors() {
  digitalWrite(LRPWM, LOW);
  digitalWrite(LLPWM, LOW);
  analogWrite(LPWM, 0);
  digitalWrite(RRPWM, LOW);
  digitalWrite(RLPWM, LOW);
  analogWrite(RPWM, 0);
}
void turnLeft() {
  digitalWrite(LRPWM, HIGH);  // Left wheel moves backward
  digitalWrite(LLPWM, LOW);
  analogWrite(LPWM, sLow);
  
  digitalWrite(RRPWM, LOW);   // Right wheel moves forward
  digitalWrite(RLPWM, HIGH);
  analogWrite(RPWM, sLow);
}

void turnRight() {
  digitalWrite(LRPWM, LOW);   // Left wheel moves forward
  digitalWrite(LLPWM, HIGH);
  analogWrite(LPWM, sLow);
  
  digitalWrite(RRPWM, HIGH);  // Right wheel moves backward
  digitalWrite(RLPWM, LOW);
  analogWrite(RPWM, sLow);
}


