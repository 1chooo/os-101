#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10 // Maximum number of processes
#define MAX_PAGES 100    // Maximum number of pages per process

// Structure to represent a process
typedef struct {
    int id;             // Process ID
    int num_pages;      // Number of pages in the process
    int pages[MAX_PAGES]; // Array to store page references
} Process;

int main() {
    int num_processes;  // Number of processes
    int delta;          // Working-set window
    int total_demand_frames = 0; // Total demand frames

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the working-set window size (Delta): ");
    scanf("%d", &delta);

    // Array of processes
    Process processes[MAX_PROCESSES];

    // Input page references for each process
    for (int i = 0; i < num_processes; i++) {
        processes[i].id = i + 1;
        printf("Enter the number of pages for Process %d: ", i + 1);
        scanf("%d", &processes[i].num_pages);
        printf("Enter the page references for Process %d:\n", i + 1);
        for (int j = 0; j < processes[i].num_pages; j++) {
            scanf("%d", &processes[i].pages[j]);
        }
    }

    // Calculate the working set for each process and total demand frames
    for (int i = 0; i < num_processes; i++) {
        int working_set = 0;
        for (int j = 0; j < delta && j < processes[i].num_pages; j++) {
            working_set += processes[i].pages[j];
        }
        total_demand_frames += working_set;
        printf("Working set for Process %d: %d\n", i + 1, working_set);
    }

    printf("Total demand frames: %d\n", total_demand_frames);

    // Check for thrashing
    int m; // Total memory frames
    printf("Enter the total memory frames (m): ");
    scanf("%d", &m);

    if (total_demand_frames > m) {
        printf("Thrashing detected!\n");
        // Implement suspension or swapping out of processes here
    } else {
        printf("No thrashing detected.\n");
    }

    return 0;
}
