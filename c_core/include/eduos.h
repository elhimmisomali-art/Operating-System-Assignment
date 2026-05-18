#ifndef EDUOS_H
#define EDUOS_H

#include <time.h>
#include <sys/types.h>

#define NEW 0
#define READY 1
#define RUNNING 2
#define WAITING 3
#define TERMINATED 4

typedef struct {
    pid_t pid;                 

    char name[64];         
    int state;                

    int priority;             

    int burst_time;       
    int remaining_time;        

    int arrival_time;          
    int memory_req_kb;        

    time_t creation_time;     

    int thread_count;         

    int exit_code;            

} PCB;

#endif