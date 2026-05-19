import subprocess
import time
import json
import os
from datetime import datetime

C_BINARY = "../c_core/eduos.exe"
PCB_FILE = "../c_core/pcb_snapshot.json"
SCHEDULER = "../python_scheduler/scheduler_sim.py"
RESULT_FILE = "../python_scheduler/simulation_results.json"
REPORT_FILE = "../controller/simulation_report.json"


def launch_c_simulator():
    print("[CONTROLLER] Launching C simulator...")

    process = subprocess.Popen(
        [C_BINARY],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )

    return process


def wait_for_pcb(timeout=15):
    print("[CONTROLLER] Monitoring PCB snapshot...")

    start = time.time()

    while True:

        if os.path.exists(PCB_FILE):

            try:
                with open(PCB_FILE, "r") as f:
                    data = json.load(f)

                if isinstance(data, list) and len(data) > 0:
                    print("[CONTROLLER] PCB snapshot loaded.")
                    return data

            except:
                pass

        if time.time() - start > timeout:
            print("[CONTROLLER] Timeout waiting for PCB snapshot.")
            return []

        time.sleep(1)


def run_scheduler():
    print("[CONTROLLER] Running scheduler...")

    result = subprocess.run(
        ["python", SCHEDULER, "--file", PCB_FILE],
        capture_output=True,
        text=True
    )

    print(result.stdout)

    if result.stderr:
        print(result.stderr)


def load_scheduler_results():

    if not os.path.exists(RESULT_FILE):
        return {}

    with open(RESULT_FILE, "r") as f:
        return json.load(f)


def generate_report(processes, scheduler_results):

    report = {
        "timestamp": str(datetime.now()),
        "status": "SUCCESS",
        "process_count": len(processes),
        "algorithms": scheduler_results,
        "generated_files": {
            "pcb_snapshot": PCB_FILE,
            "scheduler_results": RESULT_FILE,
            "gantt_charts": [
                "../docs/screenshots/FCFS_Gantt.png",
                "../docs/screenshots/SJF_Gantt.png",
                "../docs/screenshots/PRIORITY_Gantt.png",
                "../docs/screenshots/RR_Gantt.png"
            ],
            "comparison_charts": [
                "../docs/screenshots/AWT_Comparison.png",
                "../docs/screenshots/TAT_Comparison.png",
                "../docs/screenshots/CPU_Comparison.png"
            ]
        }
    }

    with open(REPORT_FILE, "w") as f:
        json.dump(report, f, indent=4)

    print("[CONTROLLER] simulation_report.json generated.")


def main():

    launch_c_simulator()

    pcb_data = wait_for_pcb()

    if not pcb_data:
        print("[CONTROLLER] No PCB data found.")
        return

    run_scheduler()

    scheduler_results = load_scheduler_results()

    generate_report(
        pcb_data,
        scheduler_results
    )

    print("[CONTROLLER] EXECUTION COMPLETE.")


if __name__ == "__main__":
    main()