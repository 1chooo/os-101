#include <stdio.h>
#include <stdbool.h>

#define R1 0
#define R2 1
#define R3 2
#define R4 3
#define NUM_RESOURCES 4

#define T1 0
#define T2 1
#define T3 2
#define NUM_TASKS 3

// Resource structure
typedef struct {
    int total;
    int available;
} Resource;

// Task structure
typedef struct {
    int holding[NUM_RESOURCES];
    int waiting[NUM_RESOURCES];
} Task;

// Initialize resources and tasks
void initialize(Resource resources[], Task tasks[]) {
    // Resource initialization
    resources[R1] = (Resource){1, 1};
    resources[R2] = (Resource){2, 2};
    resources[R3] = (Resource){1, 1};
    resources[R4] = (Resource){3, 3};

    // Task initialization
    for (int i = 0; i < NUM_TASKS; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            tasks[i].holding[j] = 0;
            tasks[i].waiting[j] = 0;
        }
    }

    // Task T1: holds one instance of R2 and is waiting for an instance of R1
    tasks[T1].holding[R2] = 1;
    resources[R2].available -= 1;
    tasks[T1].waiting[R1] = 1;

    // Task T2: holds one instance of R1, one instance of R2, and is waiting for an instance of R3
    tasks[T2].holding[R1] = 1;
    tasks[T2].holding[R2] = 1;
    resources[R1].available -= 1;
    resources[R2].available -= 1;
    tasks[T2].waiting[R3] = 1;

    // Task T3: holds one instance of R3
    tasks[T3].holding[R3] = 1;
    resources[R3].available -= 1;
}

// Print current state of resources and tasks
void printState(Resource resources[], Task tasks[]) {
    printf("Resources:\n");
    for (int i = 0; i < NUM_RESOURCES; i++) {
        printf("R%d: Total: %d, Available: %d\n", i + 1, resources[i].total, resources[i].available);
    }

    printf("\nTasks:\n");
    for (int i = 0; i < NUM_TASKS; i++) {
        printf("T%d: Holding: [", i + 1);
        for (int j = 0; j < NUM_RESOURCES; j++) {
            printf("R%d: %d ", j + 1, tasks[i].holding[j]);
        }
        printf("], Waiting: [");
        for (int j = 0; j < NUM_RESOURCES; j++) {
            printf("R%d: %d ", j + 1, tasks[i].waiting[j]);
        }
        printf("]\n");
    }
}

int main() {
    Resource resources[NUM_RESOURCES];
    Task tasks[NUM_TASKS];

    initialize(resources, tasks);
    printState(resources, tasks);

    return 0;
}
