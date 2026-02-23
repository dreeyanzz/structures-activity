#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "machine-functions.h"
#include "functions.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void printBorder();

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
			free(machine);
			machine = NULL;
			printf("Machine values has been reset.\n");

			printf("Initializing machine\n");
			machine = initMachine();
			if (machine != NULL)
				printf("Machine initialized.\n");
			else
				printf("Machine initialization failed.\n");
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
