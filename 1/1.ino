#include "motor_control.h"

void setup() {
Serial.begin(115200); 
setupMotors();

}

void loop() {
  
moveForward();
delay(3000);
stopMotors();
delay(1000);
turnRight();
delay(1000);

}
