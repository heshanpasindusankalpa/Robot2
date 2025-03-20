#include "sensor_processing.h"

void setupSensors() {
    pinMode(ULTRASONIC_TRIG, OUTPUT);
    pinMode(ULTRASONIC_ECHO, INPUT);
    pinMode(IR_FR, INPUT);
    pinMode(IR_FL, INPUT);
 
    
   
}

void sendUltrasonicData() {
    digitalWrite(ULTRASONIC_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIG, LOW);

    long duration = pulseIn(ULTRASONIC_ECHO, HIGH);
    int distance = duration * 0.034 / 2; // Convert to cm

    Serial.print("DISTANCE:");
    Serial.println(distance);
}


void sendIRSensorData() {
    int FR_value = digitalRead(IR_FR);
    int FL_value = digitalRead(IR_FL);

    Serial.print("IR SENSOR 1: ");
    Serial.println(FR_value ? "DETECTED" : "NOT DETECTED");
    
    Serial.print("IR SENSOR 2: ");
    Serial.println(FL_value ? "DETECTED" : "NOT DETECTED");
}
