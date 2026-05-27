#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>

#include "include/eduos.h"
#include "include/ipc_shared.h"

#define MAX_PROCESSES 128

PCB process_table[MAX_PROCESSES];
int process_count = 0;
static pid_t pid_counter = 1;

static void log_event(const char *msg, pid_t pid) {

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    char time_str[32];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", t);

    printf("[EDUOS-KERNEL] [TIME: %s] PID=%lld MSG=%s\n",
           time_str,
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

/* ---------------- FORK ---------------- */
pid_t edu_fork(PCB *parent) {

    PCB child = *parent;

    child.pid = pid_counter++;
    child.state = READY;
    child.creation_time = time(NULL);
    child.remaining_time = child.burst_time;
    child.owner_id = child.pid;

    process_table[process_count++] = child;

    log_event("Fork created new process", child.pid);

    return child.pid;
}

/* ---------------- EXEC ---------------- */
void edu_exec(pid_t pid, char *prog_name) {

    PCB *proc = find_process(pid);
    if (!proc) return;

    strncpy(proc->name, prog_name, sizeof(proc->name) - 1);
    proc->name[sizeof(proc->name) - 1] = '\0';

    proc->state = RUNNING;

    log_event("Exec loaded program", pid);
}

/* ---------------- WAIT ---------------- */
void edu_wait(pid_t pid) {

    PCB *proc = find_process(pid);
    if (!proc) return;

    log_event("Process waiting (simulated)", pid);

    proc->state = WAITING;

    for (volatile int i = 0; i < 100000000; i++);
}

/* ---------------- EXIT ---------------- */
void edu_exit(pid_t pid, int exit_code) {

    PCB *proc = find_process(pid);
    if (!proc) return;

    proc->state = TERMINATED;
    proc->exit_code = exit_code;

    log_event("Process terminated", pid);

    printf("[EDUOS-KERNEL] PROCESS EXIT => PID=%lld CODE=%d\n",
       (long long)pid,
        exit_code);
}

/* ---------------- MAIN ---------------- */
int main() {

    printf("EduOS Process Manager Loaded Successfully\n");

    srand(time(NULL));

    process_count = 0;
    pid_counter = 1;

    /* ---------------- CREATE PROCESSES ---------------- */
    for (int i = 0; i < 6; i++) {

        PCB p;

        p.pid = pid_counter++;
        strcpy(p.name, "process");

        p.state = READY;
        p.priority = rand() % 10;
        p.burst_time = (rand() % 10) + 1;
        p.remaining_time = p.burst_time;
        p.arrival_time = rand() % 5;
        p.memory_req_kb = (rand() % 1024) + 100;
        p.creation_time = time(NULL);
        p.thread_count = 0;
        p.exit_code = 0;
        p.owner_id = p.pid;   // 🔐 security ownership

        process_table[process_count++] = p;

        log_event("Process created", p.pid);
    }

    /* ---------------- PROCESS LIFECYCLE ---------------- */
    pid_t child = edu_fork(&process_table[0]);
    (void)child; // silence warning

    edu_exec(process_table[1].pid, "edu_program");
    edu_wait(process_table[1].pid);
    edu_exit(process_table[1].pid, 0);

    /* ---------------- IPC INTEGRATION ---------------- */


    init_shared_memory(process_table[0].pid);

    
    write_shared_memory(process_table[0].pid, "SYSTEM DATA FROM PROCESS 0");
    read_shared_memory(process_table[0].pid);

    write_shared_memory(process_table[1].pid, "HACK ATTEMPT FROM PROCESS 1");

    
    FILE *f = fopen("pcb_snapshot.json", "w");

    if (f != NULL) {

        fprintf(f, "[\n");

        for (int i = 0; i < process_count; i++) {

            PCB p = process_table[i];

            fprintf(f,
                " {\"pid\": %lld, \"burst_time\": %d, \"arrival_time\": %d, \"priority\": %d}%s\n",
                (long long)p.pid,
                p.burst_time,
                p.arrival_time,
                p.priority,
                (i == process_count - 1) ? "" : ","
            );
        }

        fprintf(f, "]\n");
        fclose(f);
    }

    return 0;
}