import random
import csv
import sys
import os

def generate_processes(n: int) -> list[dict]:
    processes = []
    for i in range(1, n + 1):
        processes.append({
            "pid":             i,
            "burst_time":      random.randint(1, 20),
            "priority":        random.randint(1, 5),
            "memory_required": random.randint(10, 500),
        })
    return processes


def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 10

    os.makedirs("data/inputs", exist_ok=True)
    filepath = "data/inputs/processes.csv"

    processes = generate_processes(n)

    with open(filepath, "w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=["pid", "burst_time", "priority", "memory_required"])
        writer.writeheader()
        writer.writerows(processes)

    print(f"Generated {n} processes → {filepath}")


if __name__ == "__main__":
    main()
import random
import csv
import sys
import os

def generate_processes(n: int) -> list[dict]:
    processes = []
    for i in range(1, n + 1):
        processes.append({
            "pid":             i,
            "burst_time":      random.randint(1, 20),
            "priority":        random.randint(1, 5),
            "memory_required": random.randint(10, 500),
        })
    return processes


def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 10

    os.makedirs("data/inputs", exist_ok=True)
    filepath = "data/inputs/processes.csv"

    processes = generate_processes(n)

    with open(filepath, "w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=["pid", "burst_time", "priority", "memory_required"])
        writer.writeheader()
        writer.writerows(processes)

    print(f"Generated {n} processes → {filepath}")


if __name__ == "__main__":
    main()