#include "algorithms.h"

int bf_find_first_free_block(int* blocks, int n, int required) {
     for (int i = 0; i < n; i++) {
         if (blocks[i] && required <= i)
             return i;
    }
    return -1;
}