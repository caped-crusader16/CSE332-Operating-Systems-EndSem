  
#include <stdio.h>
#include <stdlib.h>
  
int mutex = 1;
  
int full = 0;
  
int empty = 10;

int n = 0;
  
void producer()
{
    --mutex;
  
    ++full;
  
    --empty;
  
    n++;
    printf("\nProducer produces item %d",n);
  
    ++mutex;
}
  

void consumer()
{
    --mutex;
  
    --full;

    ++empty;
    printf("\nConsumer consumes item %d",n);
    n--;
  
    ++mutex;
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
  
            
            if ((mutex == 1)
                && (empty != 0)) {
                producer();
            }

            else {
                printf("Buffer is full!");
            }
            break;
  
        case 2:
  
            // consumer can  use
            if ((mutex == 1)
                && (full != 0)) {
                consumer();
            }
  
           
            else {
                printf("Buffer is empty!");
            }
            break;
  
        
        case 3:
            exit(0);
            break;
        }
    }
}