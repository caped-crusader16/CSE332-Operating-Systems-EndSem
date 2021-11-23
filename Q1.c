//AU1940041 Deepang Desai

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_cond_t  cond1;
pthread_cond_t  cond2;
pthread_cond_t  cond3;
pthread_mutex_t mutex;

void* Pattern1() {
        char c;
    for (c = 'A'; c <= 'Z'; ++c){
    pthread_mutex_lock(&mutex);
        printf("%c ", c);
       pthread_mutex_unlock(&mutex);
       pthread_cond_signal(&cond2); 
        pthread_cond_wait(&cond1,&mutex);
    
    }
    }

void* Pattern2() {
         int i;
    
    
    for(i = 1; i <= 26; i++){
     pthread_mutex_lock(&mutex);
     pthread_cond_wait(&cond2,&mutex);
      printf("%d ",i);
      
      pthread_mutex_unlock(&mutex);
      pthread_cond_signal(&cond3);
    }
    
    }

void* Pattern3() {
        char c;
    for (c = 'a'; c <= 'z'; ++c){
    pthread_mutex_lock(&mutex);
      pthread_cond_wait(&cond3,&mutex);
        printf("%c ", c);
        
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond1);
    
    }
    }


int main(int argc, char* argv[]) {
     pthread_t p1, p2, p3;
     pthread_mutex_init(&mutex, NULL);
     pthread_cond_init(&cond1, NULL);
     pthread_cond_init(&cond2, NULL);
     pthread_cond_init(&cond3, NULL);

    if (pthread_create(&p1, NULL, &Pattern1, NULL) != 0) {
        return 1;
    }
    if (pthread_create(&p2, NULL, &Pattern2, NULL) != 0) {
        return 2;
    }
    if (pthread_create(&p3, NULL, &Pattern3, NULL) != 0) {
        return 3;
    }
    if (pthread_join(p1, NULL) != 0) {
        return 4;
    }
    if (pthread_join(p2, NULL) != 0) {
        return 5;
    }
     if (pthread_join(p3, NULL) != 0) {
        return 6;
    }
   pthread_mutex_destroy(&mutex);
   pthread_cond_destroy(&cond1);
   pthread_cond_destroy(&cond2);
   pthread_cond_destroy(&cond3);

    
    return 0;
}