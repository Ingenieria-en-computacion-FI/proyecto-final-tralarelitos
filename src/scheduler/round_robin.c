#include <stdlib.h>
#include "scheduler.h"
#include "queue.h"
#include "circular_queue.h"

Scheduler* scheduler_create_round_robin(int quantum) {
     Scheduler* s = malloc(sizeof(Scheduler));
     s->type = SCHED_ROUND_ROBIN;
     s->fifo_q = NULL;
     s->rr_q = cq_create(16);
     s->table_cap = 16;
     s->table_size = 0;
     s->table = malloc(sizeof(SEntry) * s->table_cap);
     s->quantum = quantum;
     s->time_in_slot = 0;
     s->gantt_cap = 64;
     s->gantt_len = 0;
     s->gantt = malloc(sizeof(int) * s->gantt_cap);
     return s;
}


void scheduler_tick(Scheduler* s) {
     int pid = scheduler_next(s);
     if (pid == -1){
        return;
     }


     if (s->gantt_len == s->gantt_cap) {
         s->gantt_cap *= 2;
         s->gantt = realloc(s->gantt, sizeof(int) * s->gantt_cap);
    }
     s->gantt[s->gantt_len++] = pid;


     for (int i = 0; i < s->table_size; i++) {
         if (s->table[i].pid != pid){
             continue;
         }
         s->table[i].remaining_time--;

         if (s->type == SCHED_FIFO) {
             if (s->table[i].remaining_time <= 0){
                 dequeue(s->fifo_q);
             }
        } 
        else if (s->type == SCHED_ROUND_ROBIN) {
             s->time_in_slot++;
             if (s->table[i].remaining_time <= 0) {
                 cq_dequeue(s->rr_q);
                 s->time_in_slot = 0;
            } else if (s->time_in_slot >= s->quantum) {
                 cq_dequeue(s->rr_q);
                 cq_enqueue(s->rr_q, pid);
                 s->time_in_slot = 0;
            }
        } 
        else {
            if (s->table[i].remaining_time <= 0){
                 s->table[i].active = 0;
            }
        }
        break;
    }
}