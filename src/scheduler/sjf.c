#include <stdlib.h>
#include "scheduler.h"
#include "queue.h"
#include "circular_queue.h"

Scheduler* scheduler_create_sjf() {
     Scheduler* s = malloc(sizeof(Scheduler));
     s->type = SCHED_SJF;
     s->fifo_q = NULL;
     s->rr_q = NULL;
     s->table_cap = 16;
     s->table_size = 0;
     s->table = malloc(sizeof(SEntry) * s->table_cap);
     s->quantum = 0;
     s->time_in_slot = 0;
     s->gantt_cap = 64;
     s->gantt_len = 0;
     s->gantt = malloc(sizeof(int) * s->gantt_cap);
     return s;
}

int scheduler_next(Scheduler* s) {
     if (s->type == SCHED_FIFO){
         return queue_peek(s->fifo_q);
     }
     if (s->type == SCHED_ROUND_ROBIN){
         return cq_peek(s->rr_q);
     }


     int min_pid = -1, min_t = __INT_MAX__;
     for (int i = 0; i < s->table_size; i++) {
         if (s->table[i].active && s->table[i].remaining_time < min_t) {
             min_t = s->table[i].remaining_time;
             min_pid = s->table[i].pid;
        }
    }
     return min_pid;
}

int scheduler_is_done(Scheduler* s) {
     if (s->type == SCHED_FIFO){
         return queue_is_empty(s->fifo_q);
     }
     if (s->type == SCHED_ROUND_ROBIN){
         return cq_is_empty(s->rr_q);
     }
    

     for (int i = 0; i < s->table_size; i++) {
         if (s->table[i].active){
             return 0;
         }
    }
     return 1;
}