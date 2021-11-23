//AU1940051 Shubh Dhebar
#include<stdio.h>

int calc_times(int proc[], int n, int arrival_time[], int burst_time[], int tq, int wait_time[], int turnaroundtime[]) {
   int temp[n];
   for(int z=0;z<n;z++){
   	temp[z]=burst_time[z];
   }
   int y = n;
   int count = 0;
   int i = 0;
   int sum = 0;
   while(y>0){
   	if(temp[i] <= tq && temp[i] > 0)    
	{  
	    sum=sum + temp[i];  
	    temp[i] = 0;  
	    count=1;  
	}     
    	else if(temp[i] > 0)  
    	{  
		temp[i] = temp[i] - tq;  
		sum = sum + tq;    
    	}  
    	if(temp[i]==0 && count==1)  
    	{  
		y--;
		wait_time[i] = sum - arrival_time[i] - burst_time[i];   
		turnaroundtime[i] = sum - arrival_time[i];  
		count =0;     
    	}	  
    	if(i==n-1)  
    	{  
       	 i=0;  
    	}  
    	else if(arrival_time[i+1]<=sum)  
    	{  
        	i++;  
    	}  
    	else  
    	{  
        	i=0;  
    	}  
   }
       
}


int avgtime(int proc[], int n, int arrival_time[], int burst_time[], int tq) {
   int wait_time[n], tat[n], total_wt = 0, total_tat = 0;
   int i;
   
   calc_times(proc, n, arrival_time, burst_time, tq, wait_time, tat); 		  

   printf("Processes  Burst   WaitingTime   TurnAroundTime \n");

   for ( i=0; i<n; i++) {
      total_wt = total_wt + wait_time[i];
      total_tat = total_tat + tat[i];	   // Calculate total waiting time and total turn around time
      printf(" %d\t  %d\t\t %d \t\t%d\n", proc[i], burst_time[i], wait_time[i], tat[i]);
   }
   printf("Average waiting time = %f\n", (float)total_wt / (float)n);
   printf("Average turn around time = %f\n", (float)total_tat / (float)n);
   return 0;
}
int main(){
	int proc[] = {1, 2, 3, 4, 5, 6};   //process ids
	int arrival_time[] = {0, 1, 2, 3, 4, 5}; //arrival times
	int n = sizeof proc / sizeof proc[0];
	int burst_time[] = {7, 5, 12, 8, 9, 5};   //Burst time of all processes
	int tq=6; //time quantum
	
	avgtime(proc, n, arrival_time, burst_time, tq);
	return 0;	

}
