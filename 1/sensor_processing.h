#ifndef SENSOR_PROCESSING_H
#define SENSOR_PROCESSING_H

#include <Arduino.h>

#define ULTRASONIC_TRIG 2
#define ULTRASONIC_ECHO 3
#define IR_FR 22  
#define IR_FL 14 
#define IR_FM 15

#define S0 4
#define S1 3
#define S2 1
#define S3 0
#define sensorOut 2


void setupSensors();
//void sendUltrasonicData();
void sendIRSensorData();
void getColor();
void colorCalibrate();
int getRedPW();
int getGreenPW() ;
int getBluePW();
#endif