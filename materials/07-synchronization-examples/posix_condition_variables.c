#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond_var;
int a = 0;
int b = 0;

void* thread_function(void* arg) {
    pthread_mutex_lock(&mutex);
    while (a != b)
        pthread_cond_wait(&cond_var, &mutex);
    printf("Condition met: a == b\n");
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    
    // Initialize mutex and condition variable
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_var, NULL);
    
    // Create the thread
    pthread_create(&thread, NULL, thread_function, NULL);
    
    // Simulate some work
    printf("Main thread is doing some work...\n");
    sleep(2); // Sleep for 2 seconds
    
    // Signal the condition
    pthread_mutex_lock(&mutex);
    a = 5;
    b = 5;
    pthread_cond_signal(&cond_var);
    pthread_mutex_unlock(&mutex);
    
    // Wait for the thread to finish
    pthread_join(thread, NULL);
    
    // Cleanup
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_var);
    
    return 0;
}
