#ifndef MACHINE_FUNCTIONS_H

#define MACHINE_FUNCTIONS_H

#include "structures.h"

void initMachine(Machine *machine);
void displayAllMachineInfo(Machine *macs, int numMacs);
void computeMotorPower(Machine *mac);
void _classifyPowerLevel(Machine *mac);
void evalSensorReading(Machine *mac, int sensorIndex);
void displayMachineSensors(Machine *mac);

#endif
