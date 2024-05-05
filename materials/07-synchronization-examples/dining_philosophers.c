#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

typedef enum { THINKING, HUNGRY, EATING } state_t;

typedef struct {
    state_t state[NUM_PHILOSOPHERS];
    pthread_cond_t self[NUM_PHILOSOPHERS];
} DiningPhilosophers;

DiningPhilosophers dining_philosophers;

void init() {
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        dining_philosophers.state[i] = THINKING;
        pthread_cond_init(&dining_philosophers.self[i], NULL);
    }
}

void pickup(int i) {
    dining_philosophers.state[i] = HUNGRY;
    test(i);
    if (dining_philosophers.state[i] != EATING)
        pthread_cond_wait(&dining_philosophers.self[i], NULL);
}

void putdown(int i) {
    dining_philosophers.state[i] = THINKING;
    test((i + 4) % 5);
    test((i + 1) % 5);
}

void test(int i) {
    if ((dining_philosophers.state[(i + 4) % 5] != EATING) &&
        (dining_philosophers.state[i] == HUNGRY) &&
        (dining_philosophers.state[(i + 1) % 5] != EATING)) {
        dining_philosophers.state[i] = EATING;
        pthread_cond_signal(&dining_philosophers.self[i]);
    }
}

void* philosopher(void* arg) {
    int* philosopher_id = (int*)arg;
    while (1) {
        // Simulating thinking
        printf("Philosopher %d is thinking.\n", *philosopher_id);
        sleep(rand() % 3 + 1); // Sleep for 1-3 seconds

        // Simulating picking up chopsticks to eat
        pickup(*philosopher_id);
        printf("Philosopher %d is eating.\n", *philosopher_id);
        sleep(rand() % 3 + 1); // Sleep for 1-3 seconds

        // Simulating putting down chopsticks
        putdown(*philosopher_id);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    init();

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
