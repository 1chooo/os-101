#include <stdio.h>
#include <stdbool.h>

#define N 5 // Number of processes
#define M 3 // Number of resource types

// Function to check if all elements of Finish are true
bool isSafeState(bool Finish[N]) {
    for (int i = 0; i < N; i++) {
        if (!Finish[i])
            return false;
    }
    return true;
}

// Function to check if Need[i] <= Work
bool canProceed(int i, int Need[N][M], int Work[M]) {
    for (int j = 0; j < M; j++) {
        if (Need[i][j] > Work[j])
            return false;
    }
    return true;
}

// Safety algorithm function
bool safetyAlgorithm(int Available[M], int Max[N][M], int Allocation[N][M]) {
    int Work[M];
    bool Finish[N] = {false};
    int Need[N][M];
    
    // Initialize Work = Available
    for (int i = 0; i < M; i++) {
        Work[i] = Available[i];
    }
    
    // Calculate Need matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
    
    while (true) {
        bool found = false;
        
        for (int i = 0; i < N; i++) {
            if (!Finish[i] && canProceed(i, Need, Work)) {
                for (int j = 0; j < M; j++) {
                    Work[j] += Allocation[i][j];
                }
                Finish[i] = true;
                found = true;
            }
        }
        
        if (!found)
            break;
    }
    
    return isSafeState(Finish);
}

int main() {
    // Example data (Replace with your own data)
    int Available[M] = {3, 3, 2}; // Available resources
    int Max[N][M] = {  // Maximum resources that can be requested
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    int Allocation[N][M] = {  // Resources currently allocated
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    
    if (safetyAlgorithm(Available, Max, Allocation)) {
        printf("The system is in a safe state.\n");
    } else {
        printf("The system is not in a safe state.\n");
    }
    
    return 0;
}
