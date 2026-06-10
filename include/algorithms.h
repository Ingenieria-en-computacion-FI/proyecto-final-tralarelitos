#ifndef ALGORITHMS_H
#define ALGORITHMS_H

int bf_find_first_free_block(
     int* blocks, 
     int n, 
     int requiered
);


int greedy_first_fit(
     int* blocks,
     int* sizes,
     int n,
     int required
);

int greedy_best_fit(
     int* blocks,
     int* sizes,
     int n,
     int required
);

int greedy_worst_fit(
     int* blocks,
     int* sizes,
     int n,
     int required
);


void bt_save_state(
     int* state,
     int n
);
int bt_restore_state(
     int* state,
     int n
);


void dc_merge_free_blocks(
     int* blocks,
     int* sizes,
     int* free_flags,
     int n
);

void dc_sort_by_size(
     int* sizes,
     int* indices,
     int lo,
     int hi
);


int dp_knapsack_bottomup(
     int* weights,
     int* values,
     int n, 
     int capacity
);

int dp_knapsack_topdown(
     int* weights,
     int* values,
     int* memo,
     int n,
     int capacity
);

#endif