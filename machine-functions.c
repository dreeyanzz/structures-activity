#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "machine-functions.h"
#include "structures.h"

Machine *initMachine()
{
    Machine *machine = malloc(sizeof(Machine));
    if (machine == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // --Machine struct--
    char macName[100];
    int macId;

    printf("Enter machine name (up to 99 characters): ");
    fgets(macName, sizeof(macName), stdin);

    printf("Enter machine ID: ");
    scanf(" %d", &macId);
    while (getchar() != '\n')
        ;

    // --Motor struct--
    char motorModel[100];

    printf("Enter motor model: ");
    fgets(motorModel, sizeof(motorModel), stdin);

    // --Specifications struct--
    float specVoltage;
    float specCurrent;

    printf("Enter voltage: ");
    scanf(" %f", &specVoltage);
    while (getchar() != '\n')
        ;

    printf("Enter current: ");
    scanf(" %f", &specCurrent);
    while (getchar() != '\n')
        ;

    int numSensors;
    do
    {
        printf("Enter number of sensors (0 - 5): ");
        scanf(" %d", &numSensors);
        while (getchar() != '\n')
            ;

        if (numSensors < 0 || numSensors > 5)
            printf("Invalid number of sensors! Please enter a number between 0 and 5.\n");
    } while (numSensors < 0 || numSensors > 5);

    Sensor *sensors = (Sensor *)malloc(numSensors * sizeof(Sensor));
    int indexSen;
    for (indexSen = 0; indexSen < numSensors; indexSen++)
    {

        printf("Sensor %d:\n", indexSen + 1);

        // --Sensor struct--
        char sensorType[100];
        float sensorReading;
        float sensorMinRange;
        float sensorMaxRange;

        printf("Enter sensor type: ");
        fgets(sensorType, sizeof(sensorType), stdin);

        printf("Enter sensor reading: ");
        scanf(" %f", &sensorReading);
        while (getchar() != '\n')
            ;

        printf("Enter sensor minimum range: ");
        scanf(" %f", &sensorMinRange);
        while (getchar() != '\n')
            ;

        printf("Enter sensor maximum range: ");
        scanf(" %f", &sensorMaxRange);
        while (getchar() != '\n')
            ;

        Sensor macSensor;
        macSensor = (Sensor){
            .currentReading = sensorReading,
            .minAllowRange = sensorMinRange,
            .maxAllowRange = sensorMaxRange,
        };
        strncpy(macSensor.sensorType, sensorType, 100);

        sensors[indexSen] = macSensor;
    }

    Specifications macSpec = (Specifications){
        .voltage = specVoltage,
        .current = specCurrent,
    };

    Motor macMotor;
    strncpy(macMotor.model, motorModel, 100);
    macMotor.specs = macSpec;

    *machine = (Machine){
        .id = macId,
        .motor = macMotor,
        // .sensor = macSensor,
        .sensors = sensors,
        .numSensors = numSensors,
    };
    strncpy(machine->name, macName, 100);

    return machine;
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
    evalSensorReading(mac, sensorIndex);
}
