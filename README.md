# EduOS - Operating System Simulator

Module: 351 CS 2104  
Student: ELHIM MISOMALI  
Student ID: 25311351024  

# Project Description
EduOS is a simulated operating system that demonstrates core OS concepts such as process management, scheduling, threading, and inter-process communication using C and Python.

## Folder Structure

- c_core → C-based OS simulation (process manager, threading, IPC)
- python_scheduler → CPU scheduling algorithms
- controller → integration bridge between C and Python
- docs → reports and screenshots

## Process Management

Implemented process control using:
- edu_fork() → creates new process
- edu_exec() → replaces process program
- edu_exit() → terminates process
- edu_wait() → synchronizes parent process

## Threading

Implemented a thread pool using pthreads with:
- mutex locks
- condition variables
- task queue system

## Race Condition

Demonstrated race condition using multiple threads updating a shared counter without synchronization, then fixed using mutex locks.

## IPC (Interprocess Communication)

Implemented:
- Shared memory simulation for process data exchange
- Pipe communication between parent and child processes

## CPU Scheduling Results

The system successfully demonstrates two scheduling algorithms:

### FCFS
Processes are executed in the order they arrive in the ready queue.

### SJF
Processes are sorted based on burst time, resulting in shorter jobs being executed first.

The results clearly show different execution orders and completion times, confirming correct implementation of scheduling logic.
