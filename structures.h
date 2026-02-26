#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct Specifications
{
    float voltage;
    float current;
} Specifications;

typedef struct Sensor
{
    char sensorType[100];
    float currentReading;
    float minAllowRange;
    float maxAllowRange;
} Sensor;

typedef struct Motor
{
    char model[100];
    Specifications specs;
} Motor;

typedef struct Machine
{
    char name[100];
    int id;
    Motor motor;
    Sensor *sensors; // pointer to an array of Sensor structs
    int numSensors;
} Machine;

#endif
