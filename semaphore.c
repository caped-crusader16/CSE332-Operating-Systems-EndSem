#include<stdlib.h>
#include<stdio.h>

int S=0;
int out,in;// in used by procuder to put data and out used by consumer to consume the data 
int n=7; //total buffer legth
int full=0; //full keep trake of no of full locations
int empty=7;// , empty keep track of no of empty slots
int P ;// it is process id.
int buffer[7]= {0};

int itemC;

void wait(int sema )  {  
    while( sema <= 0) ;  
    sema--;  
}  

void signal( int sema) {
    while(sema>n);
    sema++;  
}  

int Produce_item(int p){
return rand();
}

void producer( void )  
{  
  wait ( empty );  
  wait(S);  
    
  buffer[in] = Produce_item(P);  
  in = (in + 1)% n  ;
  signal(S);  
  signal(full);  
    
}  

void consumer(void)  
{  
  wait ( empty );  
  wait(S);  
  itemC = buffer[ out ];    
out = ( out + 1 ) % n;  
  printf("Consumer %d",itemC);
  signal(S);  
  signal(empty);  
}  

 
int main()
{
    int n, i;
    printf("\n1. Press 1 for Producer"
           "\n2. Press 2 for Consumer"
           "\n3. Press 3 for Exit");
  

  
    for (i = 1; i > 0; i++) {
  
        printf("\nEnter your What to do:");
        scanf("%d", &n);
  

        switch (n) {
        case 1:
  
            
            producer();
            break;
  
        case 2:
  
            consumer();
            break;
        
        case 3:
            exit(0);
            break;
        }
    }
}