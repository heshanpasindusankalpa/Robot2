#ifndef SENSOR_PROCESSING_H
#define SENSOR_PROCESSING_H

#include <Arduino.h>

#define ULTRASONIC_TRIG 2
#define ULTRASONIC_ECHO 3

void setupSensors();
void sendUltrasonicData();
void sendIRSensorData();

#endif