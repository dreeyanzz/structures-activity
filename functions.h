#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structures.h"

float computePower(Machine *machine);
int classifyPowerLevel(float powerVal);
int checkSensorStatus(Machine *machine, int sensorIndex);
void updateSensorReading(Machine *machine, int sensorIndex, float reading);
void displayMachineInfo(Machine *machine);
float computeAverageSensorReading(Machine *machine);
int countOutOfRangeSensors(Machine *machine);
int findMachineById(Machine *machines, int numMachines, int id); // returns index of machine with matching id, or -1 if not found
float computeTotalPowerAllMachines(Machine *machines, int numMachines);
int getHighestPowerMachine(Machine *machines, int numMachines);
void removeMachine(Machine **machines, int *numMachines, int id);

#endif
