#include "algorithms.h"

static void merge(int* sizes, int* idx, int lo, int mid, int hi) {
    int  n1   = mid - lo + 1;
    int  n2   = hi  - mid;
    int* L    = (int*)__builtin_alloca(n1 * sizeof(int));
    int* R    = (int*)__builtin_alloca(n2 * sizeof(int));
    int* Li   = (int*)__builtin_alloca(n1 * sizeof(int));
    int* Ri   = (int*)__builtin_alloca(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) { L[i]  = sizes[lo + i]; Li[i] = idx[lo + i]; }
    for (int i = 0; i < n2; i++) { R[i]  = sizes[mid+1+i]; Ri[i]= idx[mid+1+i]; }

    int i = 0, j = 0, k = lo;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) { sizes[k] = L[i];  idx[k] = Li[i++]; }
        else               { sizes[k] = R[j];  idx[k] = Ri[j++]; }
        k++;
    }
    while (i < n1) { sizes[k] = L[i];  idx[k] = Li[i++]; k++; }
    while (j < n2) { sizes[k] = R[j];  idx[k] = Ri[j++]; k++; }
}

void dc_sort_by_size(int* sizes, int* indices, int lo, int hi) {
    if (lo >= hi) return;
    int mid = lo + (hi - lo) / 2;
    dc_sort_by_size(sizes, indices, lo,    mid);
    dc_sort_by_size(sizes, indices, mid+1, hi);
    merge(sizes, indices, lo, mid, hi);
}

void dc_merge_free_blocks(int* blocks, int* sizes, int* free_flags, int n) {
    /* Merge adjacent free entries */
    for (int i = 0; i < n - 1; i++) {
        if (free_flags[i] && free_flags[i+1]) {
            sizes[i]      += sizes[i+1];
            free_flags[i+1] = 0;
            blocks[i+1]     = 0;
        }
    }
}
