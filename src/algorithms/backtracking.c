#include <stdlib.h>
#include <string.h>
#include "algorithms.h"
#include "stack.h"

static Stack* history = NULL;

void bt_save_state(int* state, int n) {
    if (!history) history = stack_create();
    int* snap = malloc(sizeof(int) * (n + 1));
    snap[0] = n;
    memcpy(snap + 1, state, sizeof(int) * n);
    stack_push(history, (int)(size_t)snap);
}

int bt_restore_state(int* state, int n) {
     if (!history || stack_is_empty(history)) return 0;
     int*  snap   = (int*)(size_t)stack_pop(history);
     int   saved_n = snap[0];
     int   copy_n  = saved_n < n ? saved_n : n;
     memcpy(state, snap + 1, sizeof(int) * copy_n);
     free(snap);
     return 1;
}
