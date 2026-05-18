#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>

#include "include/eduos.h"

#define MAX_PROCESSES 128

static PCB process_table[MAX_PROCESSES];
static int process_count = 0;
static pid_t pid_counter = 1;

static void log_event(const char *msg, pid_t pid) {
    time_t now = time(NULL);
    printf("[TIME %lld] PID %lld: %s\n",
           (long long)now,
           (long long)pid,
           msg);
}

static PCB* find_process(pid_t pid) {
    for (int i = 0; i < process_count; i++) {
        if (process_table[i].pid == pid) {
            return &process_table[i];
        }
    }
    return NULL;
}

pid_t edu_fork(PCB *parent) {

    PCB child = *parent;

    child.pid = pid_counter++;
    child.state = NEW;
    child.creation_time = time(NULL);
    child.remaining_time = child.burst_time;

    process_table[process_count++] = child;

    process_table[process_count - 1].state = READY;

    log_event("Fork created new process", child.pid);

    return child.pid;
}

void edu_exec(pid_t pid, char *prog_name) {

    PCB *proc = find_process(pid);

    if (!proc) return;

    strncpy(proc->name, prog_name, sizeof(proc->name) - 1);
    proc->name[sizeof(proc->name) - 1] = '\0';

    proc->remaining_time = proc->burst_time;

    proc->state = READY;

    log_event("Exec completed", pid);
}

void edu_exit(pid_t pid, int exit_code) {

    PCB *proc = find_process(pid);

    if (!proc) return;

    proc->state = TERMINATED;
    proc->exit_code = exit_code;

    log_event("Process terminated", pid);

    printf("PID %d exited with code %d\n", pid, exit_code);
}

void write_json() {

    FILE *f = fopen("pcb_snapshot.json", "w");
    if (!f) return;

    fprintf(f, "[\n");

    for (int i = 0; i < process_count; i++) {

        PCB p = process_table[i];

        fprintf(f,
            " {\"pid\": %d, \"burst_time\": %d, \"arrival_time\": %d, \"priority\": %d}%s\n",
            p.pid,
            p.burst_time,
            p.arrival_time,
            p.priority,
            (i == process_count - 1) ? "" : ","
        );
    }

    fprintf(f, "]\n");

    fclose(f);
}

int main() {

    printf("EduOS Process Manager Loaded Successfully\n");

    srand(time(NULL));

    
    for (int i = 0; i < 5; i++) {

        PCB p;

        p.pid = pid_counter++;
        strcpy(p.name, "process");

        p.state = READY;
        p.priority = rand() % 5;
        p.burst_time = (rand() % 10) + 1;
        p.remaining_time = p.burst_time;
        p.arrival_time = rand() % 5;

        p.memory_req_kb = (rand() % 1024) + 100;
        p.creation_time = time(NULL);
        p.thread_count = 0;
        p.exit_code = 0;

        process_table[process_count++] = p;

        log_event("Process created", p.pid);
    }

    
    edu_fork(&process_table[0]);

    
    edu_exec(process_table[1].pid, "edu_program");

    
    edu_exit(process_table[1].pid, 0);


    write_json();

    return 0;
}