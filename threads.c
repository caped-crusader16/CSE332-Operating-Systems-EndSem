#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

void *printc(void *i){
    int *data = (int *)i;
    printf("%c ",*data);
}

void *printd(void *i){

   int *data = (int *)i;
    printf("%d ",*data);
}

int main(){


    pthread_t thread1,thread2,thread3;
    
    int it1,it2,it3;
    
    int i=0;


    for(i=1;i<27;i++){
        
        int small = i+96; 
        int cap = i+64;

    it1 = pthread_create(&thread1,NULL,printc,(void*) &cap);
    pthread_join(thread1,NULL);
    
    it2 = pthread_create(&thread2,NULL,printd,(void*) &i);
    pthread_join(thread2,NULL);
    
    it3 = pthread_create(&thread3,NULL,printc,(void*) &small);
    pthread_join(thread3,NULL);
    
    } 

    exit(0);
    

    return 0;
}