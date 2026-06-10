#include <assert.h>
#include "queue.h"

void test_queue_fifo() {
     Queue* queue = queue_create();

     enqueue(queue, 1);
     enqueue(queue, 2);
     enqueue(queue, 3);

     assert(dequeue(queue) == 1);
     assert(dequeue(queue) == 2);
     assert(dequeue(queue) == 3);

     queue_destroy(queue);
}
