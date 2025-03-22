#include "motor_control.h"
#include "sensor_processing.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  
#define SCREEN_HEIGHT 64  
#define OLED_RESET    -1   
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUZZER_PIN 12 
#define LED_PIN 16

int zeroCount = 0; 
bool greenDetected = false;

void setup() {
    Serial.begin(9600); 
    setupMotors();
    setupSensors();  
    pinMode(BUZZER_PIN, OUTPUT);  
    pinMode(LED_PIN, OUTPUT);  

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 initialization failed!"));
        while (true);
    }
    display.clearDisplay();
    display.display();
}

void updateOLED() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.print("Count: ");
    display.println(zeroCount);
    display.display();
}

void loop() {
   sendIRSensorData();

    while (digitalRead(IR_FR) == 1 && digitalRead(IR_FL) == 1 && digitalRead(IR_FM) == 1) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(100);
        digitalWrite(BUZZER_PIN, LOW);
        moveForward();
        sendIRSensorData();
    }

    stopMotors();
    delay(1000);

    zeroCount++;
    updateOLED();

    if (zeroCount == 1) {
      while(digitalRead(IR_B) == 1){
        moveForward();}
        stopMotors();
        delay(600);
        turnRight();
        delay(1000);

        unsigned long startTime = millis();
        while (millis() - startTime < 2000) { // Run for 2 seconds
            String detectedColor = getColor();
            if (detectedColor == "Green") {
                greenDetected = true;
                break; // Exit immediately if green is found
            }
            delay(100);
        }

        stopMotors();

        if (greenDetected) {
            Serial.println("Green Detected! Stopping...");
            digitalWrite(LED_PIN, HIGH);
            digitalWrite(BUZZER_PIN, HIGH);
            delay(500);
            digitalWrite(BUZZER_PIN, LOW);
            while (true); // Stop forever if green is detected
        } else {
            Serial.println("No Green! Checking IR sensors...");
            
            // If green is NOT detected, check IR sensors
            unsigned long irCheckStart = millis();
            while (millis() - irCheckStart < 2000) {
                if (digitalRead(IR_FR) == 1 && digitalRead(IR_FL) == 1 && digitalRead(IR_FM) == 1) {
                    stopMotors();
                    delay(2000);
                    digitalWrite(BUZZER_PIN, HIGH);
                    delay(100);
                    digitalWrite(BUZZER_PIN, LOW);
                    zeroCount++;
                    break;
                }
                delay(100);
            }

            moveForward();
            delay(600);
        }
    }
   // String color=getColor();
   // if(color=="Green"){}
   
}




