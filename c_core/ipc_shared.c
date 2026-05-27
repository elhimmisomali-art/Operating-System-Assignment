#include <stdio.h>
#include <string.h>

#include "include/eduos.h"
#include "include/ipc_shared.h"

#define SHM_SIZE 256

/* ---------------- SHARED MEMORY ---------------- */
static char shared_memory[SHM_SIZE];
static pid_t memory_owner = -1;

/* ---------------- SECURITY CHECK ---------------- */
int check_access(pid_t pid) {

    extern PCB process_table[];
    extern int process_count;

    for (int i = 0; i < process_count; i++) {

        if (process_table[i].pid == pid) {

            /* owner verification */
            if (process_table[i].owner_id == memory_owner) {
                return 1;
            }

            printf("[IPC-SHM] ACCESS DENIED | PID=%lld\n",
                   (long long)pid);

            return 0;
        }
    }

    printf("[IPC-SHM] INVALID PID | PID=%lld\n",
           (long long)pid);

    return 0;
}

/* ---------------- INIT SHARED MEMORY ---------------- */
void init_shared_memory(pid_t owner_pid) {

    memory_owner = owner_pid;

    strcpy(shared_memory, "EMPTY MEMORY");

    printf("[IPC-SHM] INIT  | OWNER=%lld\n",
           (long long)owner_pid);
}

/* ---------------- WRITE ---------------- */
void write_shared_memory(pid_t pid, const char *data) {

    if (!check_access(pid)) {
        return;
    }

    strncpy(shared_memory, data, SHM_SIZE - 1);
    shared_memory[SHM_SIZE - 1] = '\0';

    printf("[IPC-SHM] WRITE | PID=%lld | DATA=\"%s\"\n",
           (long long)pid,
           shared_memory);
}

/* ---------------- READ ---------------- */
void read_shared_memory(pid_t pid) {

    if (!check_access(pid)) {
        return;
    }

    printf("[IPC-SHM] READ  | PID=%lld | DATA=\"%s\"\n",
           (long long)pid,
           shared_memory);
}