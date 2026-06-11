import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

CSV_PATH = "reports/csv/benchmark.csv"
PNG_DIR  = "reports/png"


def plot_complexity_comparison():
    """Overlay theoretical O(n), O(n log n), O(n^2) curves against measured data."""
    df = pd.read_csv(CSV_PATH)
    n  = df["size"].values
    t  = df["mean_ms"].values

    if t[0] > 0:
        c1    = t[0] / n[0]
        c2    = t[0] / (n[0] * np.log2(n[0]))
        c3    = t[0] / (n[0] ** 2)
    else:
        c1 = c2 = c3 = 1e-6

    fig, ax = plt.subplots(figsize=(9, 5))
    ax.plot(n, t,               "o-",  label="Measured",    color="#4A90D9", linewidth=2)
    ax.plot(n, c1 * n,          "--",  label="O(n)",        color="green",   alpha=0.7)
    ax.plot(n, c2 * n * np.log2(np.maximum(n, 1)), "--",
            label="O(n log n)", color="orange",  alpha=0.7)
    ax.plot(n, c3 * n ** 2,     "--",  label="O(n²)",       color="red",     alpha=0.5)

    ax.set_title("Empirical vs Theoretical Complexity")
    ax.set_xlabel("n (processes)")
    ax.set_ylabel("Time (ms)")
    ax.legend()
    ax.grid(True, alpha=0.3)

    os.makedirs(PNG_DIR, exist_ok=True)
    out = f"{PNG_DIR}/complexity_comparison.png"
    plt.tight_layout()
    plt.savefig(out, dpi=150)
    print(f"Saved → {out}")
    plt.show()


def main():
    if not os.path.exists(CSV_PATH):
        print(f"Run benchmark.py first – {CSV_PATH} not found.")
        return
    plot_complexity_comparison()


if __name__ == "__main__":
    main()

