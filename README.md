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

# Threading system

EduOS includes a thread pool system implemented using pthreads.

Features:
Thread pool with task queue
Mutex locks for synchronization
Condition variables for thread coordination

This demonstrates concurrent execution and resource sharing

The system demonstrates:

1. Race Condition (Uncontrolled Access)

Multiple threads updating a shared variable without synchronization.

2. Fixed Version

Race condition is resolved using:

Mutex locks
Controlled critical section access

This shows the importance of synchronization in concurrent systems.

# Interprocess Communication (IPC)

EduOS implements IPC using:

Shared memory simulation
Pipe-based communication between processes

This allows data exchange between the C core and Python scheduler.

# CPU Scheduling Algorithms

EduOS supports multiple scheduling strategies:

# FCFS (First Come First Serve)
Non-preemptive scheduling
Executes processes in order of arrival

 Simple and fair
Can cause long waiting times

# SJF (Shortest Job First)
Executes processes with shortest burst time first
Improves average waiting time

 Efficient for short tasks
 May cause starvation

 Priority Scheduling
Processes selected based on priority (0–9)
Lower value = higher priority

 Flexible prioritization
 May cause starvation without aging

# Round Robin (Preemptive)
Each process gets a fixed time quantum
If not finished, it is moved to the back of the queue

 Fair CPU sharing
 Prevents starvation
 Depends on quantum size

# Scheduling Output Summary

The system generates different execution orders for each algorithm, clearly showing how CPU scheduling affects process execution.

Example outputs demonstrate:

Different start/end times
Different execution order
Fairness vs efficiency trade-offs
# System Integration

# EduOS integrates:

C-based process manager (core system)
Python scheduler (algorithm simulation)
JSON-based IPC communication

This forms a complete end-to-end OS simulation pipeline.

Scheduling Visualisation & Comparison

The system generates visual and statistical comparisons for all implemented CPU scheduling algorithms.

# Visual Outputs
FCFS, SJF, Priority, and Round Robin Gantt charts are generated using matplotlib.
Each process is assigned a unique color for clarity.
Idle CPU time is displayed in grey blocks.
All charts are saved in:
docs/screenshots/
Comparison Charts

The simulator automatically generates comparison graphs for:

Average Waiting Time (AWT)
Average Turnaround Time (TAT)
CPU Utilisation

These charts allow direct evaluation of algorithm efficiency.

Performance Table

A formatted comparison table is printed in the terminal showing:

Average Waiting Time
Average Turnaround Time
Average Response Time
CPU Utilisation
Throughput

This enables side-by-side analysis of all scheduling algorithms in a single view.

# Key Features

✔ Process lifecycle simulation
✔ Multiple CPU scheduling algorithms
✔ Thread pool implementation
✔ Race condition demonstration + fix
✔ IPC via shared memory simulation
✔ C → Python integration

# pcb_snapshot

pcb_snapshot.json is generated dynamically by the C process manager to simulate kernel-level process state updates.

simulation_report.json is generated by the Python controller after completing scheduling analysis and system integration.

# Conclusion

EduOS successfully demonstrates fundamental operating system concepts including process management, scheduling algorithms, threading, and inter-process communication.

The project highlights the trade-offs between different scheduling strategies and shows how operating systems manage resources efficiently.

# Git Commit (FINAL)

git add .
git commit -m "Final polished EduOS with full OS simulation and scheduling algorithms"
git push
