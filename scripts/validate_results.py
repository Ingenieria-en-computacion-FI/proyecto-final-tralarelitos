import pandas as pd
import sys
import os

CSV_PATH = "reports/csv/benchmark.csv"


def validate():
    if not os.path.exists(CSV_PATH):
        print(f"ERROR: {CSV_PATH} not found. Run benchmark.py first.")
        sys.exit(1)

    df = pd.read_csv(CSV_PATH)
    errors = []

    if df.isnull().values.any():
        errors.append("NaN values found in CSV.")

    if (df["mean_ms"] <= 0).any():
        errors.append("Zero or negative mean_ms found.")

    if (df["min_ms"] > df["mean_ms"]).any():
        errors.append("min_ms > mean_ms in some rows.")

    if errors:
        for e in errors:
            print(f"[FAIL] {e}")
        sys.exit(1)

    print("[PASS] All validations passed.")
    print(df.to_string(index=False))


if __name__ == "__main__":
    validate()
