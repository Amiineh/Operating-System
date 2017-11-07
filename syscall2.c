/*
 This code uses a system call to report CPU usage of our system in general, and by the current process
 Developed be Amineh Ahmadinejad
 */

#include <stdio.h>
#include<sys/time.h>
#include<unistd.h>
#define TIME_INTERVAL_MS 1000

typedef struct CpuStat{
    int user, nice, system, idle, iowait, irq, softirq;
} cpuStat;

void GetCpuInfo(FILE *file,cpuStat *cpu){
    fscanf(file, "%d %d %d %d %d %d %d", &cpu->user, &cpu->nice, &cpu->system, &cpu->idle, &cpu->iowait, &cpu->irq, &cpu->softirq);
}

int main(){
    struct timeval t0, t1;
    gettimeofday(&t0, 0);
    
    FILE* statFile = fopen("/proc/stat", "r");
    cpuStat cpu0, cpu1;
    GetCpuInfo(statFile, &cpu0);
    
    while(1){   
        gettimeofday(&t1, 0);
        float diff = (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
        if(diff >= TIME_INTERVAL_MS){
            GetCpuInfo(statFile, &cpu1);
            fclose(statFile);
            break;
        }
    }
    
    int real = (cpu1.user + cpu1.nice + cpu1.system) - (cpu0.user + cpu0.nice + cpu0.system);
    int idle = (cpu1.idle + cpu1.iowait + cpu1.irq) - (cpu0.idle + cpu0.iowait + cpu0.irq);
    
    float cpuUsage = (float)real * 100. / ((float)real + (float)idle);
    
    printf("Total cpu usage by user in %d miliseconds: %.2f%%",TIME_INTERVAL_MS, cpuUsage);
    return 0;
}

