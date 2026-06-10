#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scheduler.h"
#include "queue.h"


typedef struct {
     int pid;
     int burst_time;
     int remaining_time;
     int active;
} SEntry;

struct Scheduler {
     SchedulerType type;
     Queue* fifo_q;
     SEntry* table;
     int table_cap;
     int table_size;
     int* gantt;
     int gantt_len;
     int gantt_cap;
};

static Scheduler* sched_alloc(
     SchedulerType type,
     int quantum
){
     Scheduler* s = malloc(sizeof(Scheduler));
     s->type = type;
     s->fifo_q = (type == SCHED_FIFO) ? queue_create()  : NULL;
     s->table_cap = 16;
     s->table_size = 0;
     s->table = malloc(sizeof(SEntry) * s->table_cap);
     s->gantt_cap = 64;
     s->gantt_len = 0;
     s->gantt = malloc(sizeof(int) * s->gantt_cap);
     return s;
}

Scheduler* scheduler_create_fifo(){ 
     return sched_alloc(
         SCHED_FIFO, 
         0
    ); 
}


void scheduler_add_process(Scheduler* s, int pid, int burst_time) {
     if (s->table_size == s->table_cap) {
         s->table_cap *= 2;
         s->table = realloc(s->table, sizeof(SEntry) * s->table_cap);
    }
     s->table[s->table_size++] = (
         SEntry
    ){ 
         pid, 
         burst_time, 
         burst_time, 
         1 
    };

     if (s->type == SCHED_FIFO){
         enqueue(s->fifo_q, pid);
    }
}


int scheduler_next(Scheduler* s) {
     if (s->type == SCHED_FIFO)
         return queue_peek(s->fifo_q);
     int min_pid = -1, min_t = __INT_MAX__;
     return min_pid;
}

static void gantt_push(Scheduler* s, int pid) {
     if (s->gantt_len == s->gantt_cap) {
         s->gantt_cap *= 2;
         s->gantt = realloc(s->gantt, sizeof(int) * s->gantt_cap);
    }
     s->gantt[s->gantt_len++] = pid;
}


void scheduler_tick(Scheduler* s) {
     int pid = scheduler_next(s);
     if (pid == -1) return;
     gantt_push(s, pid);

     for (int i = 0; i < s->table_size; i++) {
         if (s->table[i].pid != pid) continue;
         s->table[i].remaining_time--;

         if (s->type == SCHED_FIFO) {
             if (s->table[i].remaining_time <= 0) dequeue(s->fifo_q);
        } 
        break;
    }
}


int scheduler_is_done(Scheduler* s) {
     if (s->type == SCHED_FIFO){
         return queue_is_empty(s->fifo_q);
     }
    return 0;
}


void scheduler_print_gantt(Scheduler* s) {
     for (int i = 0; i < s->gantt_len; i++) printf("P%d ", s->gantt[i]);
     printf("\n");
}

void scheduler_destroy(Scheduler* s) {
     if (s->fifo_q){
         queue_destroy(s->fifo_q);
     }
     free(s->table);
     free(s->gantt);
     free(s);
}
