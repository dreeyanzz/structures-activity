#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "machine-functions.h"

float computePower(Machine *machine)
{
    if (machine == NULL)
    {
        printf("Machine has not yet been initialized.\n");
        return -1.0f;
    }

    float power;

    float macCurrent = machine->motor.specs.current;
    float macVoltage = machine->motor.specs.voltage;

    power = macCurrent * macVoltage;

    return power;
}

int checkSensorStatus(Machine *machine)
{
    float maxAllow = machine->sensor.maxAllowRange;
    float minAllow = machine->sensor.minAllowRange;
    float currentReading = machine->sensor.currentReading;

    int isAllowRange = currentReading >= minAllow && currentReading <= maxAllow; // checks if `currentReading` is within range of `minAllow` and `maxAllow`

    return isAllowRange;
}

int classifyPowerLevel(float powerVal)
{
    int level;

    if (powerVal < (float)500)
        level = 1; // LOW
    else if (powerVal >= (float)500 && powerVal <= (float)1500)
        level = 2; // NORMAL
    else if (powerVal > (float)1500)
        level = 3; // HIGH

    return level;
}

void updateSensorReading(Machine *machine, float *reading)
{
    machine->sensor.currentReading = *reading;
}