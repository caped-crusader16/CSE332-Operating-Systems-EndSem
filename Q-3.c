/* Krina Khakhariya
AU1940208

Q-3 bonus question 
Describe what is Producer Consumer Problem and its solution in
detail using Semaphores and Mutex and implement it in C.*/
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#define max_items 5 // Maximum items a producer can produce or a consumer can consume
#define buffer_size 5 // Buffer size

sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int buffer[buffer_size];
pthread_mutex_t mutex;

void *producer_func(void *prod_no)
{   
    int items;
    for(int i = 0; i < max_items; i++) {
        items = rand(); // Random item will be produce here
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = items;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)prod_no),buffer[in],in);
        in = (in+1)%buffer_size;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}
void *consumer_func(void *cons_no)
{   
    int items;
    for(int i = 0; i < max_items; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n",*((int *)cons_no),items, out);
        out = (out+1)%buffer_size;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main()
{   

    pthread_t prod[5],cons[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,buffer_size);
    sem_init(&full,0,0);

    int array[5] = {1,2,3,4,5}; //Giving number to consumer and producer

    for(int i = 0; i < 5; i++) {
        pthread_create(&prod[i], NULL, (void *)producer_func, (void *)&array[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_create(&cons[i], NULL, (void *)consumer_func, (void *)&array[i]);
    }

    for(int i = 0; i < 5; i++) {
        pthread_join(prod[i], NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(cons[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
    
}