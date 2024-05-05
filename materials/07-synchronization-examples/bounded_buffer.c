#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t mutex, full, empty;

void *producer(void *arg) {
    int item = 0;
    while (1) {
        // Produce item
        item++;

        // Wait for an empty buffer slot
        sem_wait(&empty);
        sem_wait(&mutex);

        // Add item to buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        printf("Produced: %d\n", item);

        // Signal that buffer is full and release mutex
        sem_post(&mutex);
        sem_post(&full);

        // Sleep for a while to simulate work
        usleep(100000);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    while (1) {
        // Wait for a full buffer slot
        sem_wait(&full);
        sem_wait(&mutex);

        // Remove item from buffer
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumed: %d\n", item);

        // Signal that buffer is empty and release mutex
        sem_post(&mutex);
        sem_post(&empty);

        // Sleep for a while to simulate work
        usleep(200000);
    }
    pthread_exit(NULL);
}

int main(void) {
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);

    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producers[i], NULL, producer, NULL);
    }

    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    // Join threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}
