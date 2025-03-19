#include "motor_control.h"
#define LRPWM 9
#define LLPWM 10
#define LPWM 11
#define RRPWM 6
#define RLPWM 7
#define RPWM 8

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
  analogWrite(LPWM, 50);
  digitalWrite(RRPWM, LOW);
  digitalWrite(RLPWM, HIGH);
  analogWrite(RPWM, 255);
 
}

void moveBackward() {
  digitalWrite(LRPWM, HIGH);
  digitalWrite(LLPWM, LOW);
  analogWrite(LPWM, 50);
  digitalWrite(RRPWM, HIGH);
  digitalWrite(RLPWM, LOW);
  analogWrite(RPWM, 255);
 
}

void moveBackward() {
  digitalWrite(LRPWM, HIGH);
  digitalWrite(LLPWM, LOW);
  analogWrite(LPWM, 50);
  digitalWrite(RRPWM, HIGH);
  digitalWrite(RLPWM, LOW);
  analogWrite(RPWM, 255);
 
}