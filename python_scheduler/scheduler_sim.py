import json

def load_processes():
    with open("../c_core/pcb_snapshot.json", "r") as f:
        return json.load(f)

def fcfs(processes):

    time = 0
    print("\n===== FCFS SCHEDULING =====\n")

    for p in processes:

        start = time
        end = time + p["burst_time"]

        print(f"PID {p['pid']} | Start {start} | End {end}")

        time = end

import copy

def sjf(processes):

    processes_copy = copy.deepcopy(processes)

    processes_copy.sort(key=lambda x: x["burst_time"])

    time = 0

    print("\n===== SJF SCHEDULING =====\n")

    for p in processes_copy:

        start = time
        end = time + p["burst_time"]

        print(f"PID {p['pid']} | Burst {p['burst_time']} | Start {start} | End {end}")

        time = end
        
def main():
    processes = load_processes()
    fcfs(processes)
    sjf(processes)

if __name__ == "__main__":
    main()