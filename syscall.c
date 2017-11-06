#include <sys/time.h>
#include<stdio.h>
#include<time.h>


int main(){


struct timeval tval;
gettimeofday(&tval,NULL);

struct tm *timeinfo;
timeinfo=localtime(&tval.tv_sec);
printf("time is:%s",asctime(timeinfo));
return 0;
}

