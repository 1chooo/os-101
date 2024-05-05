// gcc posix_semaphores.c -o posix_semaphores -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    sem_t *sem;
    pid_t pid;

    // Create the semaphore and initialize it to 1.
    sem = sem_open("/my_semaphore", O_CREAT, 0666, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    // Fork a child process.
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process

        // Acquire the semaphore.
        if (sem_wait(sem) == -1) {
            perror("sem_wait");
            exit(EXIT_FAILURE);
        }

        // Child's critical section.
        printf("Child: Inside critical section\n");

        // Release the semaphore.
        if (sem_post(sem) == -1) {
            perror("sem_post");
            exit(EXIT_FAILURE);
        }

        printf("Child: Semaphore released\n");

        // Close semaphore in child process.
        if (sem_close(sem) == -1) {
            perror("sem_close");
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    } else {
        // Parent process

        // Acquire the semaphore.
        if (sem_wait(sem) == -1) {
            perror("sem_wait");
            exit(EXIT_FAILURE);
        }

        // Parent's critical section.
        printf("Parent: Inside critical section\n");

        // Release the semaphore.
        if (sem_post(sem) == -1) {
            perror("sem_post");
            exit(EXIT_FAILURE);
        }

        printf("Parent: Semaphore released\n");

        // Wait for the child to complete.
        wait(NULL);

        // Close and unlink semaphore in parent process.
        if (sem_close(sem) == -1) {
            perror("sem_close");
            exit(EXIT_FAILURE);
        }

        if (sem_unlink("/my_semaphore") == -1) {
            perror("sem_unlink");
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    }
}


