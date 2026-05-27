#ifndef EDUOS_H
#define EDUOS_H

#include <time.h>
#include <sys/types.h>

/* ---------------- PROCESS STATES ---------------- */
#define NEW 0
#define READY 1
#define RUNNING 2
#define WAITING 3
#define TERMINATED 4

/* ---------------- PROCESS CONTROL BLOCK ---------------- */
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

    int owner_id;

} PCB;

/* ---------------- GLOBAL SHARED PROCESS TABLE ---------------- */
/* These fix your "undefined reference" errors */
extern PCB process_table[];
extern int process_count;

/* ---------------- PROCESS SYSTEM CALLS ---------------- */
pid_t edu_fork(PCB *parent);
void edu_exec(pid_t pid, char *prog_name);
void edu_wait(pid_t pid);
void edu_exit(pid_t pid, int exit_code);

/* ---------------- IPC FUNCTIONS ---------------- */
void init_shared_memory(pid_t owner_pid);
void write_shared_memory(pid_t pid, const char *data);
void read_shared_memory(pid_t pid);
int check_access(pid_t pid);

#endif