#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Shared data
int data_set = 0;
sem_t rw_mutex, mutex;
int read_count = 0;

// Writer function
void *writer(void *arg) {
    while (1) {
        sem_wait(&rw_mutex);
        
        // Writing operation
        data_set++;
        printf("Data written by writer: %d\n", data_set);
        
        sem_post(&rw_mutex);
    }
}

// Reader function
void *reader(void *arg) {
    while (1) {
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1)
            sem_wait(&rw_mutex);
        sem_post(&mutex);
        
        // Reading operation
        printf("Data read by reader: %d\n", data_set);
        
        sem_wait(&mutex);
        read_count--;
        if (read_count == 0)
            sem_post(&rw_mutex);
        sem_post(&mutex);
    }
}

int main(void) {
    pthread_t writer_thread, reader_thread[5]; // 5 reader threads
    
    // Initialize semaphores
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);
    
    // Create writer thread
    pthread_create(&writer_thread, NULL, writer, NULL);
    
    // Create reader threads
    for (int i = 0; i < 5; i++)
        pthread_create(&reader_thread[i], NULL, reader, NULL);
    
    // Join threads
    pthread_join(writer_thread, NULL);
    for (int i = 0; i < 5; i++)
        pthread_join(reader_thread[i], NULL);
    
    // Destroy semaphores
    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);
    
    return 0;
}
