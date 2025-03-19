#include "motor_control.h"

void setup() {
Serial.begin(115200); 
setupMotors();

}

void loop() {
  
moveForward();
delay(500);
moveForward();
delay(500);

}
