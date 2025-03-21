#include "motor_control.h"
#include "sensor_processing.h"

#define BUZZER_PIN 12 // Define buzzer pin
#define LED_PIN 16


int zeroCount = 0; // Counter for (0,0) readings

void setup() {
    Serial.begin(9600); 
    setupMotors();
    setupSensors();  // Initialize sensors
    pinMode(BUZZER_PIN, OUTPUT);  // Set buzzer pin as output
    pinMode(LED_PIN, OUTPUT);  
}

void loop() {
   sendIRSensorData();

    // Move forward until both IR sensors detect no object (0,0)
    while ( digitalRead(IR_FR) == 1 &&  digitalRead(IR_FL) == 1 &&  digitalRead(IR_FM)==1) {
        moveForward();
        sendIRSensorData();  // Continuously check IR sensor values
    }

    stopMotors();  // Stop when IR sensors detect (0,0)
    delay(1000);   // Pause for 1 second

    digitalWrite(BUZZER_PIN, HIGH);  // Turn on buzzer
    delay(500);  // Buzzer on for 0.5 seconds
    digitalWrite(BUZZER_PIN, LOW);   // Turn off buzzer

    zeroCount++; // Increment count when (0,0) is detected

    if (zeroCount == 1) {  
        // First time seeing (0,0), just move forward
        moveForward();
        delay(1000);
    } 
    else if (zeroCount == 2) {  
        // Second time seeing (0,0), turn right
        turnRight();
        delay(1000);
        //zeroCount = 0; // Reset counter after turning
    }
    else if (zeroCount == 3) {
        // Third time seeing (0,0,0), check the detected color
        String detectedColor = getColor();
        if (detectedColor == "Green") {
          digitalWrite(LED_PIN,HIGH);
            stopMotors();
            Serial.println("Green color detected. Stopping.");
            while (true);  // Infinite loop to stop execution
        } else {
            Serial.print("Detected color is ");
            Serial.print(detectedColor);
            Serial.println(". Continuing forward.");
            moveForward();
            delay(1000);  // Move forward for 1 second
        }
        zeroCount = 0; // Reset counter after action
    }
}


