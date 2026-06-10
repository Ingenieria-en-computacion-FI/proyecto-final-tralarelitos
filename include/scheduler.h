#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

typedef enum {
     SCHED_FIFO,
     SCHED_ROUND_ROBIN,
     SCHED_SJF
} SchedulerType;

typedef struct Scheduler Scheduler;

Scheduler* scheduler_create_fifo();

Scheduler* scheduler_create_round_robin(
     int quantum
);

Scheduler* scheduler_create_sjf();


void scheduler_add_process(
     Scheduler* s,
     int pid,
     int burst_time
);

int scheduler_next(
     Scheduler* s
);

void scheduler_tick(
     Scheduler* s
);

int scheduler_is_done(
     Scheduler* s
);

void scheduler_print_gantt(
     Scheduler* s
);

void scheduler_destroy(
     Scheduler* s
);

#endif
