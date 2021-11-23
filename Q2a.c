#include<stdio.h>
 
void calcuate_wait_time(int n, int burst_time[], int waiting_time[], int time_quantum)
{
    int time = 0; // Time variable to keep track of time

    // Duplicate the array contents in order to prevent overwriting in 
    // the original array
    int bt[n];
    for (int i = 0 ; i < n ; i++)
        bt[i] = burst_time[i];
 
 
    // Round Robin simulation begins
    while (1)
    {
        int is_processes_terminated = 1;
 
        // Every process gets a turn
        for (int i = 0 ; i < n; i++)
        {
            // If burst time of a process is greater than 0

            if (bt[i] > 0)
            {
                is_processes_terminated = 0; // There is a pending process

                // Simulating CPU Burst

                // if burst time is greater than time quantum
                if (bt[i] > time_quantum)
                {
                    // Increase the time that the process would take
                    time += time_quantum;
 
                    // Decrease the burst time of the process by time quantum
                    bt[i] -= time_quantum;
                }
 
                // If burst time is smaller or equal than the time quantum, this is the last time process will enter the CPU.
                else
                {
                    // Increase the time that the process would take
                    time = time + bt[i];
 
                    waiting_time[i] = time - burst_time[i];
 
                    // Decrease the burst time of the process by time quantum
                    bt[i] = 0;
                }
            }
        }

        if (is_processes_terminated)
            break;
      
    }
}
 

void calculate_tat(int n, int bt[], int wt[], int tat[])
{
    for (int i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];
}
 
void calcualte_avg_time(int n, int burst_time[], int time_quantum)
{
    int waiting_time[n];
    calcuate_wait_time(n, burst_time, waiting_time, time_quantum);
    
    int tat[n];
    calculate_tat(n, burst_time, waiting_time, tat);
 
    // Print details of all processes
    printf("Processes  Burst   Waiting Turn around \n");    
    for (int i=0; i<n; i++) 
        printf(" %d\t  %d\t\t %d \t%d\n", i+1, burst_time[i], waiting_time[i], tat[i]);

    // Calculate the average waiting time
    int total_waiting_time = 0;
    for (int i=0; i<n; i++)
        total_waiting_time += waiting_time[i];
    printf("Average waiting time = %f\n", (float)total_waiting_time / (float)n);

    // Calculate the average turn around time
    int total_tat = 0;
    for (int i=0; i<n; i++)
        total_tat += tat[i];
    printf("Average turn around time = %f\n", (float)total_tat / (float)n);
 
}
 

int main()
{
    int no_of_processes = 4, time_quantum = 2;
    int burst_time[] = {10, 5, 8, 11};
    calcualte_avg_time(no_of_processes, burst_time, time_quantum);
    return 0;
}