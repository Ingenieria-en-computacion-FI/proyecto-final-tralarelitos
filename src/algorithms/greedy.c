#include "algorithms.h"


int greedy_first_fit(int* blocks, int* sizes, int n, int required) {
     for (int i = 0; i < n; i++)
         if (blocks[i] && sizes[i] >= required) return i;
     return -1;
}

int greedy_best_fit(int* blocks, int* sizes, int n, int required) {
     int best = -1;
     for (int i = 0; i < n; i++) {
         if (blocks[i] && sizes[i] >= required) {
             if (best == -1 || sizes[i] < sizes[best]) best = i;
        }
    }
     return best;
}

int greedy_worst_fit(int* blocks, int* sizes, int n, int required) {
     int worst = -1;
     for (int i = 0; i < n; i++) {
         if (blocks[i] && sizes[i] >= required) {
             if (worst == -1 || sizes[i] > sizes[worst]) worst = i;
        }
    }
     return worst;
}
