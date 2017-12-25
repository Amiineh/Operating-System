/*
 This code implements FCFS (First-come, First-served) scheduler in android kernel
 Implemented by Amineh Ahmadinejad
 */

#include <sched.h>  /* to call sched_rr_get_interval() */
#include <stdio.h>

struct timespec {
    time_t tv_sec;    /* seconds */
    long   tv_nsec;   /* nanoseconds */
};

int main(){
    int sched_rr_get_interval(pid_t pid, struct timespec * tp);
    printf("%f\n", *tp);
    return 0;
}

