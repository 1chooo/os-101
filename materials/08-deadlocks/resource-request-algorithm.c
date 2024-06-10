#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

// Global variables representing the current state
int Available[MAX_RESOURCES];
int Allocation[MAX_PROCESSES][MAX_RESOURCES];
int Need[MAX_PROCESSES][MAX_RESOURCES];

// Function prototypes
bool isSafe(int process, int request[]);
void allocateResources(int process, int request[]);
void releaseResources(int process, int release[]);

int main() {
    // Initialize Available, Allocation, and Need arrays

    // Example initialization (replace with your data)
    int numResources, numProcesses;
    printf("Enter the number of resources: ");
    scanf("%d", &numResources);
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    printf("Enter the available instances of each resource:\n");
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &Available[i]);
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &Allocation[i][j]);
        }
    }

    printf("Enter the need matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &Need[i][j]);
        }
    }

    // Request resources for a process (you can replace this with your own request)
    int process;
    printf("Enter the process number requesting resources: ");
    scanf("%d", &process);

    int request[MAX_RESOURCES];
    printf("Enter the resource request vector for process %d:\n", process);
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &request[i]);
    }

    // Check if the request can be granted
    if (isSafe(process, request)) {
        allocateResources(process, request);
        printf("Request granted. Allocation updated.\n");
    } else {
        printf("Request denied. Process must wait.\n");
    }

    return 0;
}

// Function to check if the system is in a safe state after granting a request
bool isSafe(int process, int request[]) {
    // Temporary arrays to simulate resource allocation
    int tempAvailable[MAX_RESOURCES];
    int tempAllocation[MAX_PROCESSES][MAX_RESOURCES];
    int tempNeed[MAX_PROCESSES][MAX_RESOURCES];

    // Copy current state to temporary arrays
    for (int i = 0; i < MAX_RESOURCES; i++) {
        tempAvailable[i] = Available[i];
        for (int j = 0; j < MAX_PROCESSES; j++) {
            tempAllocation[j][i] = Allocation[j][i];
            tempNeed[j][i] = Need[j][i];
        }
    }

    // Pretend to allocate requested resources
    for (int i = 0; i < MAX_RESOURCES; i++) {
        tempAvailable[i] -= request[i];
        tempAllocation[process][i] += request[i];
        tempNeed[process][i] -= request[i];
    }

    // Safety check
    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];
    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = tempAvailable[i];
    }

    int count = 0;
    while (count < MAX_PROCESSES) {
        bool found = false;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < MAX_RESOURCES; j++) {
                    if (tempNeed[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    found = true;
                    finish[i] = true;
                    count++;
                    for (int j = 0; j < MAX_RESOURCES; j++) {
                        work[j] += tempAllocation[i][j];
                    }
                    break;
                }
            }
        }
        if (!found) {
            return false; // Unsafe state
        }
    }
    return true; // Safe state
}

// Function to allocate resources to a process
void allocateResources(int process, int request[]) {
    for (int i = 0; i < MAX_RESOURCES; i++) {
        Available[i] -= request[i];
        Allocation[process][i] += request[i];
        Need[process][i] -= request[i];
    }
}

// Function to release resources from a process
void releaseResources(int process, int release[]) {
    for (int i = 0; i < MAX_RESOURCES; i++) {
        Available[i] += release[i];
        Allocation[process][i] -= release[i];
        Need[process][i] += release[i];
    }
}
