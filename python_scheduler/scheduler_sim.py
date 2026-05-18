import json
import copy


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


def sjf(processes):

    procs = copy.deepcopy(processes)
    procs.sort(key=lambda x: x["burst_time"])

    time = 0
    print("\n===== SJF SCHEDULING =====\n")

    for p in procs:
        start = time
        end = time + p["burst_time"]

        print(f"PID {p['pid']} | Burst {p['burst_time']} | Start {start} | End {end}")

        time = end

def priority_scheduling(processes):

    procs = copy.deepcopy(processes)
    time = 0
    completed = []

    print("\n===== PRIORITY SCHEDULING =====\n")

    while len(completed) < len(procs):

        ready = [p for p in procs if p not in completed and p["arrival_time"] <= time]

        if not ready:
            time += 1
            continue

        current = min(ready, key=lambda x: x["priority"])

        start = time
        end = time + current["burst_time"]

        print(f"PID {current['pid']} | Priority {current['priority']} | Start {start} | End {end}")

        time = end
        completed.append(current)


def round_robin(processes, quantum=2):

    procs = copy.deepcopy(processes)

    queue = []
    time = 0

    for p in procs:
        queue.append({
            "pid": p["pid"],
            "remaining": p["burst_time"]
        })

    print("\n===== ROUND ROBIN SCHEDULING =====\n")

    while queue:

        p = queue.pop(0)

        if p["remaining"] > quantum:

            start = time
            time += quantum
            p["remaining"] -= quantum

            print(f"PID {p['pid']} | Start {start} | End {time}")

            queue.append(p)

        else:

            start = time
            time += p["remaining"]

            print(f"PID {p['pid']} | Start {start} | End {time}")

            p["remaining"] = 0


def calculate_metrics(processes):

    print("\n===== SIMPLE METRICS (BASIC) =====\n")

    for p in processes:

        tat = p["burst_time"]   
        wt = 0

        print(f"PID {p['pid']} | TAT {tat} | WT {wt}")


def main():

    processes = load_processes()

    fcfs(processes)
    sjf(processes)
    priority_scheduling(processes)
    round_robin(processes, quantum=2)

    calculate_metrics(processes)

if __name__ == "__main__":
    main()