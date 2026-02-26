#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "machine-functions.h"
#include "functions.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void printBorder();

Machine *createTestMachines(int *numMachines);

int main(int argc, char *argv[])
{

	int numMachines = 3;

	// printf("Enter number of machines: ");
	// scanf("%d", &numMachines);

	Machine *machines = NULL;
	// machines = (Machine *)malloc(numMachines * sizeof(Machine));

	// int _indexMac;
	// for (_indexMac = 0; _indexMac < numMachines; _indexMac++)
	// 	machines[_indexMac] = *initMachine();

	machines = createTestMachines(&numMachines);

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

			int indexMac = findMachineById(machines, numMachines, macId);
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

			int indexMac = findMachineById(machines, numMachines, macId);
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

			int indexMac = findMachineById(machines, numMachines, macId);
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

			int indexMac = findMachineById(machines, numMachines, macId);
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

			int indexMac = findMachineById(machines, numMachines, macId);
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

			int indexMac = findMachineById(machines, numMachines, macId);
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

			removeMachine(&machines, &numMachines, macId);
		}
		break;

		case 11:
		{
			printf("Exiting...\n");
			exit(0);
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

Machine *createTestMachines(int *numMachines)
{
	*numMachines = 3;
	Machine *machines = (Machine *)malloc(3 * sizeof(Machine));

	// --- Machine 0: Conveyor Belt ---
	strcpy(machines[0].name, "Conveyor Belt");
	machines[0].id = 1001;
	strcpy(machines[0].motor.model, "Siemens S1-200");
	machines[0].motor.specs.voltage = 220.0f;
	machines[0].motor.specs.current = 15.5f;
	machines[0].numSensors = 2;
	machines[0].sensors = (Sensor *)malloc(2 * sizeof(Sensor));
	strcpy(machines[0].sensors[0].sensorType, "Temperature");
	machines[0].sensors[0].currentReading = 75.3f;
	machines[0].sensors[0].minAllowRange = 20.0f;
	machines[0].sensors[0].maxAllowRange = 100.0f;
	strcpy(machines[0].sensors[1].sensorType, "Vibration");
	machines[0].sensors[1].currentReading = 2.1f;
	machines[0].sensors[1].minAllowRange = 0.0f;
	machines[0].sensors[1].maxAllowRange = 5.0f;

	// --- Machine 1: Hydraulic Press ---
	strcpy(machines[1].name, "Hydraulic Press");
	machines[1].id = 1002;
	strcpy(machines[1].motor.model, "ABB M3BP-180");
	machines[1].motor.specs.voltage = 380.0f;
	machines[1].motor.specs.current = 42.0f;
	machines[1].numSensors = 3;
	machines[1].sensors = (Sensor *)malloc(3 * sizeof(Sensor));
	strcpy(machines[1].sensors[0].sensorType, "Pressure");
	machines[1].sensors[0].currentReading = 150.0f;
	machines[1].sensors[0].minAllowRange = 50.0f;
	machines[1].sensors[0].maxAllowRange = 200.0f;
	strcpy(machines[1].sensors[1].sensorType, "Temperature");
	machines[1].sensors[1].currentReading = 60.0f;
	machines[1].sensors[1].minAllowRange = 10.0f;
	machines[1].sensors[1].maxAllowRange = 90.0f;
	strcpy(machines[1].sensors[2].sensorType, "Flow Rate");
	machines[1].sensors[2].currentReading = 12.5f;
	machines[1].sensors[2].minAllowRange = 5.0f;
	machines[1].sensors[2].maxAllowRange = 20.0f;

	// --- Machine 2: Packaging Unit ---
	strcpy(machines[2].name, "Packaging Unit");
	machines[2].id = 1003;
	strcpy(machines[2].motor.model, "WEG W22-90L");
	machines[2].motor.specs.voltage = 110.0f;
	machines[2].motor.specs.current = 8.0f;
	machines[2].numSensors = 0;
	machines[2].sensors = NULL;

	return machines;
}
