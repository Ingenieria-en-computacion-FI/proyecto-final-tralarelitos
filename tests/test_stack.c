#include <assert.h>
#include "stack.h"

void test_stack_push_pop() {
     Stack* stack = stack_create();

     stack_push(stack, 10);
     stack_push(stack, 20);

     assert(stack_pop(stack) == 20);
     assert(stack_pop(stack) == 10);

     stack_destroy(stack);
}

void test_stack_empty() {
     Stack* stack = stack_create();

     assert(stack_is_empty(stack) == 1);

     stack_push(stack, 5);

     assert(stack_is_empty(stack) == 0);

     stack_destroy(stack);
}
