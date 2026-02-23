#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
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

    if (machine == NULL)
    {
        printf("Machine has not yet been initialized.\n");
        return -1;
    }

    float maxAllow = machine->sensor.maxAllowRange;
    float minAllow = machine->sensor.minAllowRange;
    float currentReading = machine->sensor.currentReading;

    int isAllowRange = currentReading >= minAllow && currentReading <= maxAllow; // checks if `currentReading` is within range of `minAllow` and `maxAllow`

    printf("Sensor allowed range: ( %.2f - %.2f )\n", minAllow, maxAllow);
    return isAllowRange;
}

int classifyPowerLevel(float powerVal)
{
    int level;

    if (powerVal < (float)500)
        level = 1; // LOW
    else if (powerVal <= (float)1500)
        level = 2; // NORMAL
    else
        level = 3; // HIGH

    return level;
}

void updateSensorReading(Machine *machine, float reading)
{
    if (machine == NULL)
    {
        printf("Machine has not yet been initialized.\n");
        return;
    }

    machine->sensor.currentReading = reading;
}
