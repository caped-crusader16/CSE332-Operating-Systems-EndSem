//AU1940041 Deepang Desai

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

sem_t seme;
sem_t semf;

pthread_mutex_t mutexBuffer;

int buffer[10];
int count = 0;

void* producer(void* args) {
    while (1) {
        
        int x = rand();
        sleep(1);

        
        sem_wait(&seme);
        pthread_mutex_lock(&mutexBuffer);
        buffer[count] = x;
        count++;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semf);
    }
}

void* consumer(void* args) {
    while (1) {
        int y;

        
        sem_wait(&semf);
        pthread_mutex_lock(&mutexBuffer);
        y = buffer[count - 1];
        count--;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&seme);

        // Consume
        printf("Got %d\n", y);
        sleep(1);
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    pthread_t th[8];
    pthread_mutex_init(&mutexBuffer, NULL);
    sem_init(&seme, 0, 10);
    sem_init(&semf, 0, 0);
    int i;
    for (i = 0; i < 8; i++) {
        if (i > 0) {
            if (pthread_create(&th[i], NULL, &producer, NULL) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&th[i], NULL, &consumer, NULL) != 0) {
                perror("Failed to create thread");
            }
        }
    }
    for (i = 0; i < 8; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    sem_destroy(&seme);
    sem_destroy(&semf);
    pthread_mutex_destroy(&mutexBuffer);
    return 0;
}