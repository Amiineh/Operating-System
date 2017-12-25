/*
 This code implements FCFS (First-come, First-served) scheduler in android kernel
 
 Each process has a burst_time (given in the input) and waiting_time.
 
 1. Calculate waiting_time of each process:
 waiting_time[i] = burst_time[i-1] + waiting_time[i-1]
 waiting_time[0] = 0
 
 2. Calculate average waiting time:
 AWT = total waiting time / number of processes
 
 3. Calculate turnaround_time for each process:
 turnaround_time[i] = waiting_time[i] + burst_time[i]
 
 4. Calculate average turnaround_time:
 ATT = total turnaround time / number of processes
 
 Implemented by Amineh Ahmadinejad
 */

#include <stdio.h>

// avoid division by zero:
#define EPSILON 0.0000001

void Cal_wt(float wt[], float bt[], int n) {
    wt[0] = 0;
    int i = 0;
    for (i = 1; i < n; i++) {
        wt[i] = wt[i-1] + bt[i-1];
    }
}

void Cal_tat(float tat[], float wt[], float bt[], int n) {
    int i = 0;
    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
    }
}

float Cal_average(float arr[], int n){
    int i = 0;
    float sum = 0.;
    for (i = 0; i < n; i++) {
        sum += arr[i];
    }
    return (float)sum / (float)(n + EPSILON);
}

int main(){
    int processes[] = {1, 2, 3};
    float bt[] = {24, 3, 3};
    int n = sizeof(processes) / sizeof(processes[0]);
    
    float wt[n];
    float tat[n];
    
    Cal_wt(wt, bt, n);
    Cal_tat(tat, wt, bt, n);
    
    float awt = Cal_average(wt, n);
    float atat = Cal_average(tat, n);
    
    printf("Processes\tBurst time\t\tWaiting time\tTurnaround time\n");
    int i = 0;
    for ( i = 0; i < n; i++) {
        printf("%d\t\t\t%f\t\t%f\t\t%f\n",processes[i], bt[i], wt[i],tat[i]);
    }
    printf("\nAverage Waiting Time: %f\nAverage Turnaround Time: %f\n\n", awt, atat);
    
    return 0;
}


