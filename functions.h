#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structures.h"

float computePower(Machine *machine);
int checkSensorStatus(Machine *machine);
int classifyPowerLevel(float powerVal);
void updateSensorReading(Machine *machine, float reading);

#endif
