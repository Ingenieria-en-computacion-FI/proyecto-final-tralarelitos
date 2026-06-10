#include <assert.h>
#include "scheduler.h"

void test_fifo_scheduler() {
     Scheduler* scheduler = scheduler_create_fifo();

     scheduler_add_process(scheduler, 1, 5);
     scheduler_add_process(scheduler, 2, 3);

     int first = scheduler_next(scheduler);

     assert(first == 1);

     scheduler_destroy(scheduler);
}
