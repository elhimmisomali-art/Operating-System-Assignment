#ifndef IPC_SHARED_H
#define IPC_SHARED_H

#include <sys/types.h>

void init_shared_memory(pid_t owner_pid);
void write_shared_memory(pid_t pid, const char *data);
void read_shared_memory(pid_t pid);
int check_access(pid_t pid);

#endif