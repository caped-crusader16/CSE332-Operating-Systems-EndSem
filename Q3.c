#include <stdio.h>
#include <stdlib.h> 

int item_no = 0, mutex = 1, empty = 5, full = 0;
  
void producer()
{
    if (!((mutex == 1) && (empty != 0)))
    {
        printf("\nBuffer full. Producer is going to sleep.");
        return;
    }
    
    --mutex;
    ++full;
    --empty;
    item_no++;

    printf("\nData Produced %d",item_no);

    ++mutex;
}
  
void consumer()
{
    if (!((mutex == 1) && (full != 0)))
    {
        printf("\nBuffer empty. Consumer is going to sleep.");
        return;
    }    
    --mutex;

    --full;
  
    ++empty;
    printf("\nData Consumed %d",item_no);
    item_no--;

    ++mutex;
}

int main()
{
    for(int i=0;i<8;i++)
    {
        producer();
    }

    for(int i=0;i<8;i++)
    {
        consumer();
    }

    printf("\n");
}