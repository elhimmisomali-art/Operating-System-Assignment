import argparse
import random
import json
from collections import deque
import matplotlib.pyplot as plt
from tabulate import tabulate


def generate_processes(n, seed=1):
    random.seed(seed)

    processes = []

    for i in range(1, n + 1):

        processes.append({
            "pid": i,
            "arrival_time": random.randint(0, 5),
            "burst_time": random.randint(1, 10),
            "priority": random.randint(0, 4)
        })

    return processes


def load_from_file(path):

    with open(path, "r") as f:
        return json.load(f)


def fcfs(processes):

    processes = sorted(
        processes,
        key=lambda x: (x["arrival_time"], x["pid"])
    )

    time = 0
    schedule = []

    for p in processes:

        if time < p["arrival_time"]:
            time = p["arrival_time"]

        start = time
        end = time + p["burst_time"]

        schedule.append((p["pid"], start, end))

        time = end

    return schedule


def sjf(processes):

    time = 0
    schedule = []
    ready = []
    remaining = processes.copy()

    while remaining or ready:

        ready += [
            p for p in remaining
            if p["arrival_time"] <= time
        ]

        remaining = [
            p for p in remaining
            if p not in ready
        ]

        if not ready:
            time += 1
            continue

        ready.sort(key=lambda x: x["burst_time"])

        p = ready.pop(0)

        start = time
        end = time + p["burst_time"]

        schedule.append((p["pid"], start, end))

        time = end

    return schedule


def priority_scheduling(processes):

    time = 0
    schedule = []
    ready = []
    remaining = processes.copy()

    while remaining or ready:

        ready += [
            p for p in remaining
            if p["arrival_time"] <= time
        ]

        remaining = [
            p for p in remaining
            if p not in ready
        ]

        if not ready:
            time += 1
            continue

        ready.sort(key=lambda x: x["priority"])

        p = ready.pop(0)

        start = time
        end = time + p["burst_time"]

        schedule.append((p["pid"], start, end))

        time = end

    return schedule


def round_robin(processes, quantum=2):

    queue = deque(
        sorted(processes, key=lambda x: x["arrival_time"])
    )

    remaining = {
        p["pid"]: p["burst_time"]
        for p in processes
    }

    time = 0
    schedule = []

    while queue:

        p = queue.popleft()

        if time < p["arrival_time"]:
            time = p["arrival_time"]

        pid = p["pid"]

        run = min(
            quantum,
            remaining[pid]
        )

        start = time
        time += run

        remaining[pid] -= run

        schedule.append((pid, start, time))

        if remaining[pid] > 0:
            queue.append(p)

    return schedule


def calculate_metrics(processes, schedule):

    completion = {}
    first_response = {}

    for pid, start, end in schedule:

        completion[pid] = end

        if pid not in first_response:
            first_response[pid] = start

    metrics = {}

    total_wait = 0
    total_tat = 0

    for p in processes:

        pid = p["pid"]

        ct = completion[pid]

        tat = ct - p["arrival_time"]

        wt = tat - p["burst_time"]

        rt = first_response[pid] - p["arrival_time"]

        metrics[str(pid)] = {
            "arrival_time": p["arrival_time"],
            "burst_time": p["burst_time"],
            "completion_time": ct,
            "turnaround_time": tat,
            "waiting_time": wt,
            "response_time": rt
        }

        total_wait += wt
        total_tat += tat

    avg_wait = total_wait / len(processes)
    avg_tat = total_tat / len(processes)

    total_time = max(end for _, _, end in schedule)

    cpu = (
        sum(p["burst_time"] for p in processes)
        / total_time
    ) * 100

    throughput = len(processes) / total_time

    return metrics, avg_wait, avg_tat, cpu, throughput


def draw_gantt(schedule, title):

    fig, ax = plt.subplots()

    colors = [
        "tab:blue",
        "tab:orange",
        "tab:green",
        "tab:red",
        "tab:purple",
        "tab:brown"
    ]

    for i, (pid, start, end) in enumerate(schedule):

        ax.barh(
            y=0,
            width=end - start,
            left=start,
            color=colors[i % len(colors)]
        )

        ax.text(
            start + (end - start) / 2,
            0,
            f"P{pid}",
            ha="center",
            va="center",
            color="white"
        )

    ax.set_title(title)

    ax.set_xlabel("Time")

    ax.set_yticks([])

    plt.savefig(
        f"../docs/screenshots/{title}.png"
    )

    plt.close()


def comparison_chart(names, values, title, filename):

    plt.figure()

    plt.bar(names, values)

    plt.title(title)

    plt.savefig(
        f"../docs/screenshots/{filename}"
    )

    plt.close()


def main():

    parser = argparse.ArgumentParser()

    parser.add_argument("--random", type=int)

    parser.add_argument("--seed", type=int, default=1)

    parser.add_argument("--file", type=str)

    parser.add_argument("--quantum", type=int, default=2)

    args = parser.parse_args()

    if args.file:
        processes = load_from_file(args.file)
    else:
        processes = generate_processes(
            args.random or 5,
            args.seed
        )

    results = {}

    algorithms = {
        "FCFS": fcfs(processes),
        "SJF": sjf(processes),
        "PRIORITY": priority_scheduling(processes),
        "ROUND_ROBIN": round_robin(
            processes,
            args.quantum
        )
    }

    table = []

    names = []
    waits = []
    tats = []
    cpus = []

    for name, schedule in algorithms.items():

        metrics, avg_wait, avg_tat, cpu, throughput = calculate_metrics(
            processes,
            schedule
        )

        results[name] = {
            "schedule": schedule,
            "metrics": metrics,
            "avg_waiting_time": avg_wait,
            "avg_turnaround_time": avg_tat,
            "cpu_utilisation": cpu,
            "throughput": throughput
        }

        draw_gantt(
            schedule,
            f"{name}_Gantt"
        )

        names.append(name)
        waits.append(avg_wait)
        tats.append(avg_tat)
        cpus.append(cpu)

        table.append([
            name,
            round(avg_wait, 2),
            round(avg_tat, 2),
            round(cpu, 2),
            round(throughput, 2)
        ])

    comparison_chart(
        names,
        waits,
        "Average Waiting Time",
        "AWT_Comparison.png"
    )

    comparison_chart(
        names,
        tats,
        "Average Turnaround Time",
        "TAT_Comparison.png"
    )

    comparison_chart(
        names,
        cpus,
        "CPU Utilisation",
        "CPU_Comparison.png"
    )

    print(
        tabulate(
            table,
            headers=[
                "Algorithm",
                "Avg WT",
                "Avg TAT",
                "CPU %",
                "Throughput"
            ],
            tablefmt="grid"
        )
    )

    with open("simulation_results.json", "w") as f:
        json.dump(results, f, indent=4)


if __name__ == "__main__":
    main()