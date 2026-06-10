#include <stdlib.h>
#include <stdio.h>
#include "scheduler.h"
#include "queue.h"
#include "circular_queue.h"

Scheduler* scheduler_create_fifo() {
     Scheduler* s = malloc(sizeof(Scheduler));
     s->type = SCHED_FIFO;
     s->fifo_q = queue_create();
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

void scheduler_add_process(
     Scheduler* s,
     int pid,
     int burst_time
){
     if (s->table_size == s->table_cap) {
         s->table_cap *= 2;
         s->table = realloc(
             s->table,
             sizeof(SEntry) * s->table_cap
        );
    }
     s->table[s->table_size++] = (SEntry){ pid, burst_time, burst_time, 1 };

     if (s->type == SCHED_FIFO){
         enqueue(
             s->fifo_q,
             pid
        );
     }
     else if (s->type == SCHED_ROUND_ROBIN){
         cq_enqueue(
             s->rr_q,
             pid
        );
     }
}

void scheduler_print_gantt(Scheduler* s) {
     const char* names[] = {"FIFO", "RoundRobin", "SJF"};
     printf("[%s Gantt] ", names[s->type]);
     for (int i = 0; i < s->gantt_len; i++){
         printf("P%d ", s->gantt[i]);
     }
     printf("\n");
}

void scheduler_destroy(Scheduler* s) {
     if (s->fifo_q){
         queue_destroy(s->fifo_q);
     }
     if (s->rr_q){
         cq_destroy(s->rr_q);
     }
     free(s->table);
     free(s->gantt);
     free(s);
}