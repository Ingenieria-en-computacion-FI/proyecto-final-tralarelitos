import subprocess
import time
import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

SIZES    = [10, 50, 100, 500, 1000, 5000]
RUNS     = 3          
BIN      = "./bin/main"  
CSV_OUT  = "reports/csv/benchmark.csv"
PNG_OUT  = "reports/png/benchmark.png"


def run_once(size: int) -> float:
    subprocess.run(
        ["python", "scripts/generate_process.py", str(size)],
        capture_output=True
    )
    start = time.perf_counter()
    subprocess.run([BIN, str(size)], capture_output=True)
    end = time.perf_counter()
    return (end - start) * 1000.0


def benchmark() -> pd.DataFrame:
    results = []
    for size in SIZES:
        times = [run_once(size) for _ in range(RUNS)]
        results.append({
            "size":    size,
            "mean_ms": round(np.mean(times), 4),
            "std_ms":  round(np.std(times),  4),
            "min_ms":  round(np.min(times),  4),
            "max_ms":  round(np.max(times),  4),
        })
        print(f"  n={size:>5}  mean={results[-1]['mean_ms']:.2f} ms")
    return pd.DataFrame(results)


def plot(df: pd.DataFrame):
    fig, axes = plt.subplots(1, 2, figsize=(12, 5))
    fig.suptitle("Mini OS Simulator – Real Benchmark Data", fontsize=14)

    ax1 = axes[0]
    ax1.errorbar(df["size"], df["mean_ms"], yerr=df["std_ms"],
                 marker="o", capsize=4, color="#4A90D9", linestyle="-")
    ax1.set_title("Execution time vs Process count")
    ax1.set_xlabel("Number of processes (n)")
    ax1.set_ylabel("Time (ms)")
    ax1.grid(True, alpha=0.3)

    ax2 = axes[1]
    x   = np.arange(len(df))
    w   = 0.25
    ax2.bar(x - w, df["min_ms"],  width=w, label="min",  color="#4A90D9")
    ax2.bar(x,     df["mean_ms"], width=w, label="mean", color="#F5A623")
    ax2.bar(x + w, df["max_ms"],  width=w, label="max",  color="#D0021B")
    ax2.set_xticks(x)
    ax2.set_xticklabels(df["size"])
    ax2.set_title("Min / Mean / Max per size")
    ax2.set_xlabel("Number of processes (n)")
    ax2.set_ylabel("Time (ms)")
    ax2.legend()
    ax2.grid(True, alpha=0.3, axis="y")

    plt.tight_layout()
    os.makedirs("reports/png", exist_ok=True)
    plt.savefig(PNG_OUT, dpi=150)
    print(f"\n[OK] Gráfica guardada exitosamente en → {PNG_OUT}")
    plt.show()


def main():
    os.makedirs("reports/csv", exist_ok=True)
    print("Iniciando Benchmark Real...")
    print("---------------------------------------")
    df = benchmark()
    print("---------------------------------------")
    df.to_csv(CSV_OUT, index=False)
    print(f"[OK] Tabla de datos guardada en → {CSV_OUT}\n")
    print(df.to_string(index=False))
    print("\nGenerando gráficas visuales...")
    plot(df)


if __name__ == "__main__":
    main()