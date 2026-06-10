#include <stdio.h>

void test_stack_push_pop();
void test_stack_empty();
void test_queue_fifo();
void test_round_robin_behavior();
void test_fifo_scheduler();
void test_first_fit();

int main() {
     printf("Running integration tests...\n");

     test_stack_push_pop();
     test_stack_empty();

     test_queue_fifo();

     test_round_robin_behavior();

     test_fifo_scheduler();

     test_first_fit();

     test_bruteforce();

     test_greedy();

     test_dp();

     printf("All tests passed!\n");

     return 0;
}
