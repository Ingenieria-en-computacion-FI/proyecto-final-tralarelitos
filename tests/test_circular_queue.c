#include <assert.h>
#include "circular_queue.h"

void test_round_robin_behavior() {
     CircularQueue* q = cq_create(3);

     cq_enqueue(q, 1);
     cq_enqueue(q, 2);
     cq_enqueue(q, 3);

     assert(cq_dequeue(q) == 1);

     cq_enqueue(q, 4);

     assert(cq_dequeue(q) == 2);
     assert(cq_dequeue(q) == 3);
     assert(cq_dequeue(q) == 4);

     cq_destroy(q);
}
