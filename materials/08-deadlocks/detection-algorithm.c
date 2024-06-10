#include <stdio.h>
#include <stdbool.h>

#define MAX_RESOURCES 10
#define MAX_PROCESSES 10

int available[MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int request[MAX_PROCESSES][MAX_RESOURCES];
bool finish[MAX_PROCESSES];

// Function to initialize the arrays
void initialize(int m, int n) {
    int i, j;
    for (i = 0; i < m; i++) {
        finish[i] = true;
        for (j = 0; j < n; j++) {
            if (allocation[i][j] != 0) {
                finish[i] = false;
                break;
            }
        }
    }
}

// Function to detect deadlock
bool detectDeadlock(int m, int n) {
    int work[MAX_RESOURCES];
    bool found;
    int i, j;

    // Copy available resources to work
    for (i = 0; i < m; i++) {
        work[i] = available[i];
    }

    // Iterate until all processes are finished or deadlock detected
    do {
        found = false;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    // Allocate resources
                    for (j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                }
            }
        }
    } while (found);

    // Check for deadlock
    for (i = 0; i < n; i++) {
        if (!finish[i]) {
            return true;
        }
    }
    return false;
}

int main() {
    int m, n;
    printf("Enter the number of resources: ");
    scanf("%d", &m);
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the request matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    initialize(m, n);

    if (detectDeadlock(m, n)) {
        printf("Deadlock detected.\n");
    } else {
        printf("No deadlock detected.\n");
    }

    return 0;
}
