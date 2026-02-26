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

	int numMachines;

	printf("Enter number of machines: ");
	scanf("%d", &numMachines);
	while (getchar() != '\n')
		;

	Machine *machines = (Machine *)malloc(numMachines * sizeof(Machine));

	int _indexMac;
	for (_indexMac = 0; _indexMac < numMachines; _indexMac++)
	{
		printf("\n--- Machine %d ---\n", _indexMac + 1);
		initMachine(&machines[_indexMac]);
	}

	int choice;
	while (1)
	{
		printBorder();
		printf("\n");

		printf("===== INDUSTRIAL MACHINE MONITORING SYSTEM =====\n");
		printf("1. Display All Machines\n");
		printf("2. Compute and Classify Power of a Machine\n");
		printf("3. Check Sensor Status\n");
		printf("4. Update Sensor Reading\n");
		printf("5. Compute Average Sensor Reading\n");
		printf("6. Count Out-of-Range Sensors\n");
		printf("7. Find Machine by ID\n");
		printf("8. Compute Total Power of All Machines\n");
		printf("9. Show Machine with Highest Power\n");
		printf("10. Remove Machine\n");
		printf("11. Exit\n");

		printf("\nEnter your choice: ");
		scanf(" %d", &choice);

		switch (choice)
		{
		case 1:
		{
			printf("You selected: Display All Machines\n");
			displayAllMachineInfo(machines, numMachines);
		}
		break;

		case 2:
		{
			printf("You selected: Compute and Classify Power of a Machine\n");

			printf("Enter machine ID to compute power: ");
			int macId;
			scanf(" %d", &macId);
			while (getchar() != '\n')
				;

			int indexMac = findMachineByID(machines, numMachines, macId);
			if (indexMac == -1)
				break;

			computeMotorPower(&machines[indexMac]);
			_classifyPowerLevel(&machines[indexMac]);
		}
		break;

		case 3:
		{
			printf("You selected: Check Sensor Status\n");

			printf("Enter machine ID to check sensor status: ");
			int macId;
			scanf(" %d", &macId);
			while (getchar() != '\n')
				;

			int indexMac = findMachineByID(machines, numMachines, macId);
			if (indexMac == -1)
				break;

			Machine *mac = &machines[indexMac];
			displayMachineSensors(mac);

			printf("Enter sensor index to check (0 - %d): ", mac->numSensors - 1);
			int sensorIndex;
			scanf(" %d", &sensorIndex);
			while (getchar() != '\n')
				;

			evalSensorReading(mac, sensorIndex);
		}
		break;

		case 4:
		{
			printf("You selected: Update Sensor Reading\n");

			printf("Enter machine ID to update sensor reading: ");
			int macId;
			scanf(" %d", &macId);
			while (getchar() != '\n')
				;

			int indexMac = findMachineByID(machines, numMachines, macId);
			if (indexMac == -1)
				break;

			Machine *mac = &machines[indexMac];
			_updateSensorReading(mac);
		}
		break;

		case 5:
		{
			printf("You selected: Compute Average Sensor Reading\n");

			printf("Enter machine ID to compute average sensor reading: ");
			int macId;
			scanf(" %d", &macId);
			while (getchar() != '\n')
				;

			int indexMac = findMachineByID(machines, numMachines, macId);
			if (indexMac == -1)
				break;

			float aveReading = computeAverageSensorReading(&machines[indexMac]);
			if (aveReading == -1.0f)
				break;

			printf("Average sensor reading for machine %d: %.2f\n", macId, aveReading);
		}
		break;

		case 6:
		{
			printf("You selected: Count Out-of-Range Sensors\n");

			printf("Enter machine ID to count out-of-range sensors: ");
			int macId;
			scanf(" %d", &macId);
			while (getchar() != '\n')
				;

			int indexMac = findMachineByID(machines, numMachines, macId);
			if (indexMac == -1)
				break;

			int count = countOutOfRangeSensors(&machines[indexMac]);
			if (count == -1)
				break;

			printf("Number of out-of-range sensors for machine %d: %d\n", macId, count);
		}
		break;

		case 7:
		{
			printf("You selected: Find Machine by ID\n");

			printf("Enter machine ID to find: ");
			int macId;
			scanf(" %d", &macId);
			while (getchar() != '\n')
				;

			int indexMac = findMachineByID(machines, numMachines, macId);
			if (indexMac == -1)
				break;

			printf("Machine found at index %d:\n", indexMac);
			displayMachineInfo(&machines[indexMac]);
		}
		break;

		case 8:
		{
			printf("You selected: Compute Total Power of All Machines\n");

			float totalPower = computeTotalPowerAllMachines(machines, numMachines);

			if (totalPower == -1.0f)
				break;

			printf("Total power of all machines: %.2f\n", totalPower);
		}
		break;

		case 9:
		{
			printf("You selected: Show Machine with Highest Power\n");

			int indexHighest = getHighestPowerMachine(machines, numMachines);
			if (indexHighest == -1)
				break;

			printf("Machine with highest power:\n");
			displayMachineInfo(&machines[indexHighest]);
		}
		break;

		case 10:
		{
			printf("You selected: Remove Machine\n");

			printf("Enter machine ID to remove: ");
			int macId;
			scanf(" %d", &macId);
			while (getchar() != '\n')
				;

			removeMachine(machines, &numMachines, macId);
		}
		break;

		case 11:
		{
			printf("Exiting...\n");
			free(machines);
			return 0;
		}
		break;

		default:
			printf("Invalid choice. Please try again.\n");
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
