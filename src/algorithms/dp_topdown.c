#include <stdlib.h>
#include "algorithms.h"

int dp_knapsack_topdown(int* weights, int* values, int* memo, int n, int capacity) {
     if (n == 0 || capacity == 0) return 0;
     int key = n * 10000 + capacity;
     if (memo[key] != -1) return memo[key];

     if (weights[n-1] > capacity) {
         memo[key] = dp_knapsack_topdown(weights, values, memo, n-1, capacity);
    } else {
         int without = dp_knapsack_topdown(weights, values, memo, n-1, capacity);
         int with = values[n-1] + dp_knapsack_topdown(weights, values, memo, n-1, capacity - weights[n-1]);
         memo[key] = without > with ? without : with;
    }
     return memo[key];
}
