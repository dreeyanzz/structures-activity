#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "functions.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void printBorder();
Machine *createTestMachine();

Machine *initMachine();
void displayMachineInfo(Machine *mac);

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
		printf("  5. Evaluate sensor status\n");
		printf("  6. Display all information in a structured format\n");
		printf("\n");

		printf("\nChoice: ");
		scanf(" %d", &choice);
		while (getchar() != '\n')
			;

		switch (choice)
		{
		case 1:
		{
			printf("You have chosen %d\n", choice);
			machine = createTestMachine();
		}
		break;

		case 2:
		{
			printf("You have chosen %d\n", choice);
		}
		break;

		case 3:
		{
			printf("You have chosen %d\n", choice);
		}
		break;

		case 4:
		{
			printf("You have chosen %d\n", choice);
		}
		break;

		case 5:
		{
			printf("You have chosen %d\n", choice);
		}
		break;

		case 6:
		{
			printf("You have chosen %d\n", choice);
			displayMachineInfo(machine);
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

	printf("{\n");
	printf("  \"name\": \"%s\",\n", mac->name);
	printf("  \"id\": %d,\n", mac->id);
	printf("  \"motor\": {\n");
	printf("    \"model\": \"%s\",\n", mac->motor.model);
	printf("    \"specs\": {\n");
	printf("      \"voltage\": %.2f,\n", mac->motor.specs.voltage);
	printf("      \"current\": %.2f\n", mac->motor.specs.current);
	printf("    }\n");
	printf("  },\n");
	printf("  \"sensor\": {\n");
	printf("    \"type\": \"%s\",\n", mac->sensor.sensorType);
	printf("    \"currentReading\": %.2f,\n", mac->sensor.currentReading);
	printf("    \"minAllowRange\": %.2f,\n", mac->sensor.minAllowRange);
	printf("    \"maxAllowRange\": %.2f\n", mac->sensor.maxAllowRange);
	printf("  }\n");
	printf("}\n");
}