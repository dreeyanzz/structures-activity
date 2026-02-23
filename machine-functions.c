#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "machine-functions.h"
#include "structures.h"

Machine *initMachine()
{
    Machine *machine = malloc(sizeof(Machine));

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

    Specifications macSpec = (Specifications){
        .voltage = specVoltage,
        .current = specCurrent,
    };

    Motor macMotor;
    strncpy(macMotor.model, motorModel, 100);
    macMotor.specs = macSpec;

    Sensor macSensor;

    macSensor = (Sensor){
        .currentReading = sensorReading,
        .minAllowRange = sensorMinRange,
        .maxAllowRange = sensorMaxRange,
    };
    strncpy(macSensor.sensorType, sensorType, 100);

    *machine = (Machine){
        .id = macId,
        .motor = macMotor,
        .sensor = macSensor,
    };
    strncpy(machine->name, macName, 100);

    return machine;
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
    mac->sensor.sensorType[strcspn(mac->sensor.sensorType, "\n")] = '\0';

    printf("Machine\n");
    printf("|- name: %s\n", mac->name);
    printf("|- id: %d\n", mac->id);
    printf("|- motor\n");
    printf("|   |- model: %s\n", mac->motor.model);
    printf("|   |- specs\n");
    printf("|       |- voltage: %.2f\n", mac->motor.specs.voltage);
    printf("|       |- current: %.2f\n", mac->motor.specs.current);
    printf("|- sensor\n");
    printf("    |- type: %s\n", mac->sensor.sensorType);
    printf("    |- currentReading: %.2f\n", mac->sensor.currentReading);
    printf("    |- minAllowRange: %.2f\n", mac->sensor.minAllowRange);
    printf("    |- maxAllowRange: %.2f\n", mac->sensor.maxAllowRange);
}

void computeMotorPower(Machine *mac)
{
    float power = computePower(mac);

    if (power < 0)
        return;

    printf("Motor Power: %.2f\n", power);
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
        levelStr = "LOW";
        break;
    case 2:
        levelStr = "NORMAL";
        break;
    case 3:
        levelStr = "HIGH";
        break;
    default:
        levelStr = "UNKNOWN";
        break;
    }

    printf("Power Level: %s\n", levelStr);
}
