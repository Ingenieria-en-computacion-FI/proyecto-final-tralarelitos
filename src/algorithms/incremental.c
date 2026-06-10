#include "algorithms.h"

int dp_knapsack_incremental(int* weights, int* values, int n, int capacity) {
     int* dp = (int*)__builtin_alloca(sizeof(int) * (capacity + 1));
     for (int w = 0; w <= capacity; w++) dp[w] = 0;

     for (int i = 0; i < n; i++) {
         for (int w = capacity; w >= weights[i]; w--) {
             int with_item = dp[w - weights[i]] + values[i];
             if (with_item > dp[w]) dp[w] = with_item;
        }
    }
     return dp[capacity];
}
