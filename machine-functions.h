#ifndef MACHINE_FUNCTIONS_H

#define MACHINE_FUNCTIONS_H

#include "structures.h"

Machine *initMachine();
void displayMachineInfo(Machine *mac);
void computeMotorPower(Machine *mac);
void _classifyPowerLevel(Machine *mac);
void evalSensorReading(Machine *mac);

#endif
