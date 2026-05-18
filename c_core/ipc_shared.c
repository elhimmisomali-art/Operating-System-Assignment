#include <stdio.h>
#include <string.h>

typedef struct {
    int pid;
    int cpu_usage;
    int memory_usage;
} SharedData;

int main() {

    SharedData data;

    data.pid = 1;
    data.cpu_usage = 45;
    data.memory_usage = 128;

    printf("Shared Memory Simulation:\n");
    printf("PID: %d | CPU: %d | MEM: %d\n",
           data.pid, data.cpu_usage, data.memory_usage);

    return 0;
}