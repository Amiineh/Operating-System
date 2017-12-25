/*
 This code implements SJF (Shortest Job First) scheduler in android kernel
 
 Each process has a burst_time (given in the input) and waiting_time.
 
 1. Sort the processes
 2. Use previous FCFS
 
 Implemented by Amineh Ahmadinejad
 */

#include <stdio.h>

// avoid division by zero:
#define EPSILON 0.0000001

typedef struct Process{
    int pid; // Process ID
    float bt;  // Burst Time
} process;

void insertion_sort(process a[], int n) {
    size_t i = 0;
    for (i = 1; i < n; i++) {
        process tmp = a[i];
        size_t j = i;
        while(j > 0 && (tmp.bt - a[j - 1].bt) < 0) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = tmp;
    }
}

void Cal_wt(process processes[], float wt[], int n) {
    wt[0] = 0;
    int i = 0;
    for (i = 1; i < n; i++) {
        wt[i] = wt[i-1] + processes[i-1].bt;
    }
}

void Cal_tat(process processes[], float tat[], float wt[], int n) {
    int i = 0;
    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + processes[i].bt;
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
    process processes[] = {{1, 24}, {2, 3}, {3, 3}};
    int n = sizeof(processes) / sizeof(processes[0]);
    
    float wt[n];
    float tat[n];
    
    insertion_sort(processes, n);
    Cal_wt(processes, wt, n);
    Cal_tat(processes, tat, wt, n);
    
    float awt = Cal_average(wt, n);
    float atat = Cal_average(tat, n);
    
    printf("Processes\tBurst time\t\tWaiting time\tTurnaround time\n");
    int i = 0;
    for ( i = 0; i < n; i++) {
        printf("%d\t\t\t%f\t\t%f\t\t%f\n",processes[i].pid, processes[i].bt, wt[i],tat[i]);
    }
    printf("\nAverage Waiting Time: %f\nAverage Turnaround Time: %f\n\n", awt, atat);
    
    return 0;
}



