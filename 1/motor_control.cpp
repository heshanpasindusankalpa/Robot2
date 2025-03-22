#include "motor_control.h"
#define LRPWM 9
#define LLPWM 10
#define LPWM 11
#define RRPWM 6
#define RLPWM 7
#define RPWM 8
// Encoder Pins
#define ENCODER_A_L 44  // Left encoder A phase
#define ENCODER_B_L 45  // Left encoder B phase
#define ENCODER_A_R 24 // Right encoder A phase
#define ENCODER_B_R 25 // Right encoder B phase


#define sLow 90


volatile int leftCount = 0;
volatile int rightCount = 0;

float Kp = 1.5, Ki = 0, Kd = 0;
float error = 0, prevError = 0, integral = 0, derivative = 0;
int baseSpeed = 65;

void setupMotors() {
 
pinMode(LRPWM, OUTPUT);
pinMode(LLPWM, OUTPUT);
pinMode(LPWM, OUTPUT);
pinMode(RRPWM, OUTPUT);
pinMode(RLPWM, OUTPUT);
pinMode(RPWM, OUTPUT);

pinMode(ENCODER_A_L, INPUT);
pinMode(ENCODER_B_L, INPUT);
pinMode(ENCODER_A_R, INPUT);
pinMode(ENCODER_B_R, INPUT);

     
}

void moveForward() {
  digitalWrite(LRPWM, HIGH);
  digitalWrite(LLPWM, LOW);
  analogWrite(LPWM, sLow);
  digitalWrite(RRPWM, LOW);
  digitalWrite(RLPWM, HIGH);
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
void turnRight() {
  digitalWrite(LRPWM, HIGH);  // Left wheel moves backward
  digitalWrite(LLPWM, LOW);
  analogWrite(LPWM, sLow);
  
  digitalWrite(RRPWM, HIGH);   // Right wheel moves forward
  digitalWrite(RLPWM, LOW);
  analogWrite(RPWM, sLow);
}

void turnLeft() {
  digitalWrite(LRPWM, LOW);   // Left wheel moves forward
  digitalWrite(LLPWM, HIGH);
  analogWrite(LPWM, sLow);
  
  digitalWrite(RRPWM, LOW);  // Right wheel moves backward
  digitalWrite(RLPWM, HIGH);
  analogWrite(RPWM, sLow);
}
void movePIDForward(int leftSpeed, int rightSpeed) {
  digitalWrite(LRPWM, HIGH);
  digitalWrite(LLPWM, LOW);
  analogWrite(LPWM, leftSpeed);
  digitalWrite(RRPWM, LOW);
  digitalWrite(RLPWM, HIGH);
  analogWrite(RPWM, rightSpeed);
}

// Interrupt routines to count encoder ticks
void leftEncoderISR() {
  if (digitalRead(ENCODER_A_L) == digitalRead(ENCODER_B_L)) leftCount++;
  else leftCount--;
}

void rightEncoderISR() {
  if (digitalRead(ENCODER_A_R) == digitalRead(ENCODER_B_R)) rightCount++;
  else rightCount--;
}

// PID speed correction
void applyPID() {
  int leftSpeedMeasured = leftCount;   // Measured speed from encoder
  int rightSpeedMeasured = rightCount; // Measured speed from encoder

  leftCount = 0;  // Reset counters
  rightCount = 0;

  error = leftSpeedMeasured - rightSpeedMeasured; // Difference between left and right wheel

  integral += error;   // Integral part (accumulated error)
  derivative = error - prevError; // Derivative part (rate of change)

  int correction = Kp * error + Ki * integral + Kd * derivative;

  int leftSpeed = baseSpeed - correction;  // Declare leftSpeed
  int rightSpeed = baseSpeed + correction; // Declare rightSpeed

  // Constrain values to prevent exceeding PWM range
  leftSpeed = constrain(leftSpeed, 50, 255);
  rightSpeed = constrain(rightSpeed, 50, 255);

  moveForward(); // You need to modify moveForward() to accept parameters if required.

  prevError = error; // Update previous error
}


