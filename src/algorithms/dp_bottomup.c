#include <stdlib.h>
#include "algorithms.h"

int dp_knapsack_bottomup(int* weights, int* values, int n, int capacity) {
     int** dp = malloc(sizeof(int*) * (n + 1));
     for (int i = 0; i <= n; i++)
         dp[i] = calloc(capacity + 1, sizeof(int));

     for (int i = 1; i <= n; i++) {
         for (int w = 0; w <= capacity; w++) {
             dp[i][w] = dp[i-1][w];
             if (weights[i-1] <= w) {
                 int with_item = dp[i-1][w - weights[i-1]] + values[i-1];
                 if (with_item > dp[i][w]) dp[i][w] = with_item;
            }
        }
    }

     int result = dp[n][capacity];
     for (int i = 0; i <= n; i++) free(dp[i]);
     free(dp);
     return result;
}
