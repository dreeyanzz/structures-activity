#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "machine-functions.h"
#include "structures.h"

void initMachine(Machine *machine)
{
    printf("Enter machine name (up to 99 characters): ");
    fgets(machine->name, sizeof(machine->name), stdin);
    machine->name[strcspn(machine->name, "\n")] = '\0';

    printf("Enter machine ID: ");
    scanf(" %d", &machine->id);
    while (getchar() != '\n')
        ;

    printf("Enter motor model: ");
    fgets(machine->motor.model, sizeof(machine->motor.model), stdin);
    machine->motor.model[strcspn(machine->motor.model, "\n")] = '\0';

    printf("Enter voltage: ");
    scanf(" %f", &machine->motor.specs.voltage);
    while (getchar() != '\n')
        ;

    printf("Enter current: ");
    scanf(" %f", &machine->motor.specs.current);
    while (getchar() != '\n')
        ;

    do
    {
        printf("Enter number of sensors (0 - 5): ");
        scanf(" %d", &machine->numSensors);
        while (getchar() != '\n')
            ;

        if (machine->numSensors < 0 || machine->numSensors > 5)
            printf("Invalid number of sensors! Please enter a number between 0 and 5.\n");
    } while (machine->numSensors < 0 || machine->numSensors > 5);

    int indexSen;
    for (indexSen = 0; indexSen < machine->numSensors; indexSen++)
    {
        printf("Sensor %d:\n", indexSen + 1);

        printf("Enter sensor type: ");
        fgets(machine->sensors[indexSen].sensorType, sizeof(machine->sensors[indexSen].sensorType), stdin);
        machine->sensors[indexSen].sensorType[strcspn(machine->sensors[indexSen].sensorType, "\n")] = '\0';

        printf("Enter sensor reading: ");
        scanf(" %f", &machine->sensors[indexSen].currentReading);
        while (getchar() != '\n')
            ;

        printf("Enter sensor minimum range: ");
        scanf(" %f", &machine->sensors[indexSen].minAllowRange);
        while (getchar() != '\n')
            ;

        printf("Enter sensor maximum range: ");
        scanf(" %f", &machine->sensors[indexSen].maxAllowRange);
        while (getchar() != '\n')
            ;
    }
}

void displayAllMachineInfo(Machine *macs, int numMacs)
{
    int indexMac;
    for (indexMac = 0; indexMac < numMacs; indexMac++)
    {
        printf("Machine %d:\n", indexMac + 1);
        displayMachineInfo(&macs[indexMac]);
        printf("\n");
    }
}

void displayMachineSensors(Machine *mac)
{
    const int numSensors = mac->numSensors;

    int indexSen;
    for (indexSen = 0; indexSen < numSensors; indexSen++)
    {
        char pipe = indexSen == numSensors - 1 ? ' ' : '|';

        Sensor sensor = mac->sensors[indexSen];
        printf("     |- Sensor %d:\n", indexSen + 1);
        printf("     %c   |- type: %s\n", pipe, sensor.sensorType);
        printf("     %c   |- currentReading: %.2f\n", pipe, sensor.currentReading);
        printf("     %c   |- minAllowRange: %.2f\n", pipe, sensor.minAllowRange);
        printf("     %c   |- maxAllowRange: %.2f\n", pipe, sensor.maxAllowRange);
        int isInRange = sensor.currentReading >= sensor.minAllowRange && sensor.currentReading <= sensor.maxAllowRange;
        printf("     %c   |- status: %s\n", pipe, isInRange ? "NORMAL" : "OUT OF RANGE");
    }
}

void computeMotorPower(Machine *mac)
{
    float power = computePower(mac);

    if (power < 0)
        return;

    printf("Motor Power: %.2fW\n", power);
}

void _classifyPowerLevel(Machine *mac)
{
    float power = computePower(mac);

    if (power < 0)
        return;

    int level = classifyPowerLevel(power);

    char *levelStr;

    switch (level)
    {
    case 1:
        levelStr = "LOW POWER";
        break;
    case 2:
        levelStr = "NORMAL POWER";
        break;
    case 3:
        levelStr = "HIGH POWER";
        break;
    default:
        levelStr = "UNKNOWN";
        break;
    }

    printf("Power Level: %s\n", levelStr);
}

void evalSensorReading(Machine *mac, int sensorIndex)
{
    int status = checkSensorStatus(mac, sensorIndex);

    if (status == -1)
        return;

    char *statusStr = status ? "Sensor reading is within allowed range." : "Sensor reading is outside allowed range.";

    printf("Sensor Status: %s\n", statusStr);
}

void _updateSensorReading(Machine *mac)
{

    if (mac == NULL)
    {
        printf("Machine has not yet been initialized.\n");
        return;
    }

    char answer[4];

    do
    {
        printf("Do you want to update sensor reading? (yes or no): ");
        scanf("%3s", answer);

        if (strcmp(answer, "yes") != 0 && strcmp(answer, "no") != 0)
            printf("Invalid input!\n");

    } while (strcmp(answer, "yes") != 0 && strcmp(answer, "no") != 0);

    if (strcmp(answer, "no") == 0)
        return;

    printf("Select sensor index to update (0 - %d): ", mac->numSensors - 1);
    int sensorIndex;
    scanf(" %d", &sensorIndex);
    while (getchar() != '\n')
        ;

    float sensorReading;
    printf("Enter sensor reading: ");
    scanf("%f", &sensorReading);
    updateSensorReading(mac, sensorIndex, sensorReading);

    printf("Updated sensor reading to %.2f\n", sensorReading);
}
