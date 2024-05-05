#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex; // Declare the mutex globally

void* thread_function(void* arg) {
    int* thread_id = (int*)arg;

    // Acquire the mutex lock
    pthread_mutex_lock(&mutex);

    // Critical section
    printf("Thread %d is in critical section.\n", *thread_id);

    // Release the mutex lock
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t threads[5]; // Array to hold thread IDs
    int thread_args[5];   // Array to hold thread arguments

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create 5 threads
    for (int i = 0; i < 5; ++i) {
        thread_args[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_args[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
