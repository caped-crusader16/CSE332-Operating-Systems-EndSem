#include<stdio.h>
#include<pthread.h>
#include<time.h>

pthread_t Thread_id[3];
pthread_mutex_t mutex;
unsigned int rc;

int UpperCs = 65;
int LowerCs = 97;
int num = 1;
int fg = 0;
void* PrintCapitals(void*);
void* PrintLowers(void*);
void* PrintNos(void*);

void main(void)
{
    pthread_create(&Thread_id[0],0,&PrintCapitals,0);
    pthread_create(&Thread_id[1],0,&PrintNos,0);
    
    pthread_create(&Thread_id[2],0,&PrintLowers,0);
    


    pthread_join(Thread_id[0],NULL);
    pthread_join(Thread_id[1],NULL);
    pthread_join(Thread_id[2],NULL);

}

void* PrintCapitals(void *ptr)
{
     rc = pthread_mutex_lock(&mutex);
     while(UpperCs<=90)
     {
     if(fg%3==0){
     
            printf("%c ",UpperCs);
        UpperCs++;
            fg++;
     
     }
     else{
            rc=pthread_mutex_unlock(&mutex);
         
     } 
}

void* PrintLowers(void* ptr1)
{
    rc = pthread_mutex_lock(&mutex);
    while(LowerCs<=122)
    {
      if(fg%3==2){
      printf("%c ",LowerCs);
        LowerCs++;
        fg++;
   
      }
      else{
            rc=pthread_mutex_unlock(&mutex);
      }
      
         
    }
}

void* PrintNos(void* ptr1)
{
    rc = pthread_mutex_lock(&mutex);
   while(num <= 26)
    {
    if(fg%3==1){
     printf("%d ",num);
        num++;
        fg++;
    }
    else{
                rc=pthread_mutex_unlock(&mutex);
        }
         
    }
}