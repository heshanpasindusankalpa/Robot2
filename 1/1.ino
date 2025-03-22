#include "motor_control.h"
#include "sensor_processing.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width
#define SCREEN_HEIGHT 64  // OLED display height
#define OLED_RESET    -1   // Reset pin (not needed for some screens)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUZZER_PIN 12 // Define buzzer pin
#define LED_PIN 16

int zeroCount = 0; // Counter for (0,0) readings

void setup() {
    Serial.begin(9600); 
    setupMotors();
    setupSensors();  // Initialize sensors
    pinMode(BUZZER_PIN, OUTPUT);  // Set buzzer pin as output
    pinMode(LED_PIN, OUTPUT);  

    // Initialize OLED display
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 initialization failed!"));
        while (true); // Stop execution if OLED fails
    }
    display.clearDisplay();
    display.display();
}

void updateOLED() {
    display.clearDisplay();
    display.setTextSize(2);  // Set text size
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.print("Count: ");
    display.println(zeroCount);
    display.display();
}

void loop() {
    sendIRSensorData();

    while (digitalRead(IR_FR) == 1 && digitalRead(IR_FL) == 1 && digitalRead(IR_FM) == 1) {
        applyPID();
        sendIRSensorData();  // Continuously check IR sensor values
    }

    stopMotors();
    delay(1000);

    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);

    zeroCount++;

    updateOLED();

    if (zeroCount == 1) {
        // After first zeroCount, delay
       // delay(1500); // Add delay here as required
        while (zeroCount < 2) {  // Keep turning until zeroCount == 2
            turnRight();
            // Check if zeroCount changes during turning
            if (digitalRead(IR_FR) == 1 && digitalRead(IR_FL) == 1 && digitalRead(IR_FM) == 1) {
                stopMotors();
                delay(2000);  // Pause to detect properly
                digitalWrite(BUZZER_PIN, HIGH);
                delay(200);
                digitalWrite(BUZZER_PIN, LOW);
                zeroCount++;
                updateOLED();
            }
        }
        stopMotors();  // Stop after turning
    }

    applyPID(); // Keep applying PID for consistent control
}


