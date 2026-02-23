#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "machine-functions.h"
#include "functions.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void printBorder();
Machine *createTestMachine();

int main(int argc, char *argv[])
{
	int choice;
	Machine *machine = NULL;

	while (1)
	{
		printBorder();
		printf("\n");

		printf("Select action:\n");
		printf("  1. Initialize machine\n");
		printf("  2. Compute motor power\n");
		printf("  3. Classify power level\n");
		printf("  4. Evaluate sensor status\n");
		printf("  5. Update sensor reading\n");
		printf("  6. Display all information in a structured format\n");
		printf("  7. Exit\n");
		printf("\n");

		printf("\nChoice: ");
		scanf(" %d", &choice);
		while (getchar() != '\n')
			;

		switch (choice)
		{
		case 1:
		{	
			printf("Machine values has been reset.\n");
			machine = NULL;
		
			printf("Initializing machine\n");	
			machine = initMachine();
			printf("Machine initialized.\n");
		}
		break;

		case 2:
		{
			printf("Computing motor power\n");
			computeMotorPower(machine);
		}
		break;

		case 3:
		{
			printf("Classifying power level\n");
			_classifyPowerLevel(machine);
		}
		break;

		case 4:
		{
			printf("Evaluating sensor reading\n");
			evalSensorReading(machine);
		}
		break;

		case 5:
		{
			printf("Updating sensor reading\n");
			_updateSensorReading(machine);
		}
		break;

		case 6:
		{
			printf("Machine info:\n");
			displayMachineInfo(machine);
		}
		break;
		
		case 7:
		{
			printf("Exiting...\n");
			free(machine);
			exit(0);
		}
		break;
		

		default:
			printf("Invalid choice");
			break;
		}
	}

	return 0;
}

void printBorder()
{
	int i;
	for (i = 0; i < 50; i++)
		printf("-");
}

Machine *createTestMachine()
{
	Machine *machine = malloc(sizeof(Machine));
	if (machine == NULL)
		return NULL;

	Specifications macSpec = (Specifications){
		.voltage = 220.0f,
		.current = 15.5f,
	};

	Motor macMotor;
	strncpy(macMotor.model, "ABB M3AA 180", 100);
	macMotor.specs = macSpec;

	Sensor macSensor = (Sensor){
		.currentReading = 45.7f,
		.minAllowRange = 20.0f,
		.maxAllowRange = 80.0f,
	};
	strncpy(macSensor.sensorType, "Temperature", 100);

	*machine = (Machine){
		.id = 1,
		.motor = macMotor,
		.sensor = macSensor,
	};
	strncpy(machine->name, "Test Machine 1", 100);

	return machine;
}
