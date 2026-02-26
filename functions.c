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

int checkSensorStatus(Machine *machine, int sensorIndex)
{

    if (machine == NULL)
    {
        printf("Machine has not yet been initialized.\n");
        return -1;
    }

    if (sensorIndex < 0 || sensorIndex >= machine->numSensors)
    {
        printf("Invalid sensor index! Please enter a number between 0 and %d.\n", machine->numSensors - 1);
        return -1;
    }

    Sensor sensor = machine->sensors[sensorIndex];
    float maxAllow = sensor.maxAllowRange;
    float minAllow = sensor.minAllowRange;
    float currentReading = sensor.currentReading;

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

void updateSensorReading(Machine *machine, int sensorIndex, float reading)
{
    if (machine == NULL)
    {
        printf("Machine has not yet been initialized.\n");
        return;
    }

    if (sensorIndex < 0 || sensorIndex >= machine->numSensors)
    {
        printf("Invalid sensor index! Please enter a number between 0 and %d.\n", machine->numSensors - 1);
        return;
    }

    machine->sensors[sensorIndex].currentReading = reading;
}

void displayMachineInfo(Machine *mac)
{
    if (mac == NULL)
    {
        printf("Machine has not yet been initialized.\n");
        return;
    }

    mac->name[strcspn(mac->name, "\n")] = '\0';
    mac->motor.model[strcspn(mac->motor.model, "\n")] = '\0';

    int indexSen;
    for (indexSen = 0; indexSen < mac->numSensors; indexSen++)
        mac->sensors[indexSen].sensorType[strcspn(mac->sensors[indexSen].sensorType, "\n")] = '\0';

    printf(" |- name: %s\n", mac->name);
    printf(" |- id: %d\n", mac->id);
    printf(" |- motor\n");
    printf(" |   |- model: %s\n", mac->motor.model);
    printf(" |   |- specs\n");
    printf(" |       |- voltage: %.2fV\n", mac->motor.specs.voltage);
    printf(" |       |- current: %.2fA\n", mac->motor.specs.current);
    printf(" |- sensors (%d)\n", mac->numSensors);
    displayMachineSensors(mac);
}

float computeAverageSensorReading(Machine *machine) // returns average of currentReading values of all sensors in machine; if machine is not initialized, returns -1.0f
{
    if (machine == NULL)
    {
        printf("Machine has not yet been initialized.\n");
        return -1.0f;
    }

    float sum = 0.0f;
    int numSensors = machine->numSensors;

    int indexSen;
    for (indexSen = 0; indexSen < numSensors; indexSen++)
        sum += machine->sensors[indexSen].currentReading;

    return sum / (float)numSensors;
}

int countOutOfRangeSensors(Machine *machine)
{
    if (machine == NULL)
    {
        printf("Machine has not yet been initialized.\n");
        return -1;
    }

    int count = 0;
    int numSensors = machine->numSensors;

    int indexSen;
    for (indexSen = 0; indexSen < numSensors; indexSen++)
        if (!checkSensorStatus(machine, indexSen))
            count++;

    return count;
}

int findMachineById(Machine *machines, int numMachines, int id) // returns index of machine with matching id, or -1 if not found
{
    if (machines == NULL)
    {
        printf("Machines have not yet been initialized.\n");
        return -1;
    }

    int indexMac;
    for (indexMac = 0; indexMac < numMachines; indexMac++)
        if (machines[indexMac].id == id)
            return indexMac;

    printf("No machine found with ID %d.\n", id);
    return -1;
}

float computeTotalPowerAllMachines(Machine *machines, int numMachines)
{
    if (machines == NULL)
    {
        printf("Machines have not yet been initialized.\n");
        return -1.0f;
    }

    float totalPower = 0.0f;

    int indexMac;
    for (indexMac = 0; indexMac < numMachines; indexMac++)
        totalPower += computePower(&machines[indexMac]);

    return totalPower;
}

int getHighestPowerMachine(Machine *machines, int numMachines) // returns index of machine with highest power, or -1 if machines is not initialized
{
    if (machines == NULL)
    {
        printf("Machines have not yet been initialized.\n");
        return -1;
    }

    int highestIndex = 0;
    float highestPower = computePower(&machines[0]);

    int indexMac;
    for (indexMac = 1; indexMac < numMachines; indexMac++)
    {
        float power = computePower(&machines[indexMac]);
        if (power > highestPower)
        {
            highestPower = power;
            highestIndex = indexMac;
        }
    }

    return highestIndex;
}

void removeMachine(Machine **machines, int *numMachines, int id) // removes machine with matching id from machines array, and updates numMachines; if no machine with matching id is found or machines is not initialized, does nothing
{
    if (machines == NULL || *machines == NULL)
    {
        printf("Machines have not yet been initialized.\n");
        return;
    }

    int indexToRemove = findMachineById(*machines, *numMachines, id);
    if (indexToRemove == -1)
        return;

    free((*machines)[indexToRemove].sensors);

    int indexMac;
    for (indexMac = indexToRemove; indexMac < *numMachines - 1; indexMac++)
        (*machines)[indexMac] = (*machines)[indexMac + 1];

    (*numMachines)--;
    *machines = (Machine *)realloc(*machines, (*numMachines) * sizeof(Machine));
}