#include "motor_control.h"
#include "sensor_processing.h"

void setup() {
    Serial.begin(9600); 
    setupMotors();
    setupSensors();  // Initialize sensors
}

void loop() {
    sendIRSensorData();  

    // Move forward until both IR sensors detect no object (0)
    while (digitalRead(IR_FL) == 1 && digitalRead(IR_FR) == 1) {
        moveForward();
        sendIRSensorData();  // Continuously check IR sensor values
    }

    stopMotors();  // Stop when IR sensors detect something
    delay(1000);   // Pause for 1 second

    turnRight();   // Turn right after stopping
    delay(1000);   // Delay for turn completion
}

