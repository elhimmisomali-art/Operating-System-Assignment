# EduOS - Operating System Simulator

## Module Information
- Module Code: 351 CS 2104
- Student Name: ELHIM MISOMALI
- Registration Number: 25311351024

## Project Overview
EduOS is a simplified Operating System simulator developed using C and Python. 
The project demonstrates core Operating System concepts including process management, 
threading, CPU scheduling, IPC (shared memory), synchronization, deadlock simulation, 
and protection/security mechanisms.

The simulator mimics real Linux system calls such as fork(), exec(), wait(), and exit() 
through custom implementations like edu_fork(), edu_exec(), edu_wait(), and edu_exit().

---

# Prerequisites

Before running the project, install:

## C Environment
- MSYS2 UCRT64
- GCC Compiler
- Make utility

## Python Environment
- Python 3.10+
- matplotlib
- numpy

Install Python libraries using:

```bash
pip install matplotlib numpy
```

---

# Build and Run Instructions

## Step 1 — Open MSYS2 UCRT64

Navigate to the C core directory:

```bash
cd /c/users/YOUR_USERNAME/Downloads/EduOS-25311351024/c_core
```

## Step 2 — Clean Previous Builds

```bash
make clean
```

## Step 3 — Compile the Simulator

```bash
make all
```

## Step 4 — Run the Simulator

```bash
./process_manager.exe
```

---

# Running the Python Scheduler

Navigate to:

```bash
cd ../python_scheduler
```

Run:

```bash
python scheduler_sim.py --file ../c_core/pcb_snapshot.json
```

---

# Annotated Directory Tree

```
EduOS-25311351024/
│
├── c_core/
│   ├── process_manager.c       # Main OS process simulation
│   ├── ipc_shared.c            # Shared memory IPC + protection
│   ├── thread_manager.c        # Thread pool simulation
│   ├── producer_consumer.c     # Producer-consumer synchronization
│   ├── race_demo.c             # Race condition demonstration
│   ├── deadlock_demo.c         # Deadlock simulation
│   ├── include/
│   │   ├── eduos.h             # PCB structures and system API
│   │   └── ipc_shared.h        # IPC function declarations
│   └── Makefile                # Build automation
│
├── python_scheduler/
│   ├── scheduler_sim.py        # CPU scheduling simulator
│   └── simulation_results.json # Scheduling metrics
│
├── controller/
│   ├── controller.py           # Main orchestrator
│   └── simulation_report.json  # Final generated report
│
├── docs/
│   └── screenshots/            # Screenshots and charts
│
└── README.md
```

---

# Operating System Concepts Demonstrated

## System Calls
- edu_fork() → Linux fork(2)
- edu_exec() → Linux execve(2)
- edu_wait() → Linux wait(2)
- edu_exit() → Linux _exit(2)

## IPC and Protection
Shared memory communication is implemented in ipc_shared.c.
Only processes with matching owner_id fields are allowed access.

## OS Structure
- Kernel Simulation:
  - process_manager.c
  - ipc_shared.c
- User Space:
  - controller.py
  - scheduler_sim.py

## Virtual Machine Concept
Each PCB acts like an isolated virtual process environment, similar to guest isolation in Type-2 hypervisors.

---

# Sample Output

```text
[EDUOS-KERNEL] PID=1 MSG=STATE=CREATED
[EDUOS-KERNEL] PID=2 MSG=SYS=EXEC
[IPC-SHM] WRITE | PID=1
[IPC-SHM] ACCESS DENIED | PID=2
```

Final Summary Line:

```text
0 errors from 0 contexts
```

---

# Screenshots

## Screenshot 1 — Process Manager Running
[Process Manager Running](docs/screenshots/process_manager.png)

## Screenshot 2 — IPC Shared Memory Demonstration
[IPC Shared Memory Security](docs/screenshots/ipc_security.png)

## Screenshot 3 — Scheduler Output and Gantt Charts
[FCFS_GANTT chart](docs/screenshots/FCFS_Gantt.png)
[SJF_GANTT chart](docs/screenshot/SJF_Gantt.png)
[RR_GANTT chart](docs/screenshot/RR_Gantt.png)
[PRIORITY_GANTT chart](docs/screenshots/Priority_Gantt.png)
---

# Challenges Encountered

## 1. Multiple Definition of main()
Problem:
Several C files contained separate main() functions causing linker errors.

Solution:
Each file was compiled separately through the Makefile.

---

## 2. IPC Linking Errors
Problem:
ipc_shared.c could not access process_table and process_count.

Solution:
Global shared variables were declared using extern in eduos.h.

---

## 3. Header File Visibility Problems
Problem:
Compiler produced implicit declaration errors.

Solution:
Correct include paths and header declarations were added.

---

# References

1. Operating System Concepts — Abraham Silberschatz
2. Linux man pages:
   - fork(2)
   - execve(2)
   - wait(2)
3. GNU GCC Documentation
4. POSIX Threads Documentation
5. Course lecture notes

---

# .gitignore

```gitignore
*.o
*.out
*.exe
__pycache__/
*.pyc
venv/
.DS_Store
