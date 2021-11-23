#include<stdio.h>
#include<stdlib.h>

int max(int num1, int num2){
    return (num1 > num2 ) ? num1 : num2;
}

void waitTime(int proc[],int n,int bust[],int wait[]){
    int q = 4;
    int remain_bust[n] ;
    int remain_p = n;

    int i=0;
    int tw = 0;

    wait[0] = 0;
    remain_bust[0] = max(bust[0]-q,0);
    tw=bust[0] - remain_bust[0];

    bust[0] = remain_bust[0];


    if(!remain_bust[0]){
        remain_p--;
    }


    while (remain_p>0){
         i++;
        if(i==n){
            i=0;
        }    

        if(!bust[i]){
            continue;
        }

        wait[i] = tw;

        remain_bust[i] = max(bust[i]-q,0);
        tw += (bust[i] - remain_bust[i]);

        bust[i] = remain_bust[i];
    
        if(!remain_bust[i]){
            remain_p--;
        }

       
    }

}

void tatTime(int proc[],int n,int bust[],int wait[],int tat[]){
 int i;
   for ( i = 0; i < n ; i++)
	   tat[i] = bust[i] + wait[i];	// calculating turnaround time by adding
}


void averageTime(
int proc[],int n,int bust[]

){
int wait_time[n],tat[n],total_wt=0,total_tat=0;
int bust_c[n];

int i=0;
for(i=0;i<n;i++){

    bust_c[i] = bust[i];
}
    waitTime(proc,n,bust_c,wait_time);
    tatTime(proc,n,bust,wait_time,tat);

    printf("Processes  Burst   Waiting Turn around \n");

    for ( i=0; i<n; i++) {
      total_wt = total_wt + wait_time[i];
      total_tat = total_tat + tat[i];	   // Calculate total waiting time and total turn around time
      printf(" %d\t  %d\t\t %d \t%d\n", i+1, bust[i], wait_time[i], tat[i]);
   }
   printf("Average waiting time = %f\n", (float)total_wt / (float)n);
   printf("Average turn around time = %f\n", (float)total_tat / (float)n);



}



int main(){

    int pid[5] = {1,2,3,4,5};
    int n = 5;
    int bust_time[5] = { 3,6,4,5,2};
    int arrival[5] = {0,0,0,0,0};

    averageTime(pid,n,bust_time);

    return 0;
}