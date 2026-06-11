#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"
#include "scheduler.h"
#include "memory_manager.h"
#include "stack.h"
#include "queue.h"
#include "circular_queue.h"
#include "linked_list.h"
#include "doubly_linked_list.h"
#include "logger.h"
#include "timer.h"
#include "parser.h"


static void demo_fifo() {
     printf("\n=== FIFO Scheduler ===\n");
     Scheduler* s = scheduler_create_fifo();
     scheduler_add_process(s, 1, 4);
     scheduler_add_process(s, 2, 2);
     scheduler_add_process(s, 3, 3);
     while (!scheduler_is_done(s)) scheduler_tick(s);
     scheduler_print_gantt(s);
     scheduler_destroy(s);
}

static void demo_round_robin() {
     printf("\n=== Round Robin (quantum=2) ===\n");
     Scheduler* s = scheduler_create_round_robin(2);
     scheduler_add_process(s, 1, 5);
     scheduler_add_process(s, 2, 3);
     scheduler_add_process(s, 3, 4);
     while (!scheduler_is_done(s)) scheduler_tick(s);
     scheduler_print_gantt(s);
     scheduler_destroy(s);
}

static void demo_sjf() {
     printf("\n=== Shortest Job First ===\n");
     Scheduler* s = scheduler_create_sjf();
     scheduler_add_process(s, 1, 6);
     scheduler_add_process(s, 2, 2);
     scheduler_add_process(s, 3, 4);
     while (!scheduler_is_done(s)) scheduler_tick(s);
     scheduler_print_gantt(s);
     scheduler_destroy(s);
}

static void demo_memory() {
     printf("\n=== Memory Manager ===\n");
     MemoryManager* mm = mm_create(1000);

     int a1 = mm_allocate_first_fit(mm, 200);
     int a2 = mm_allocate_first_fit(mm, 300);
     int a3 = mm_allocate_first_fit(mm, 100);
     printf("Allocated at: %d, %d, %d\n", a1, a2, a3);
     mm_print(mm);

     mm_free(mm, 200);
     mm_free(mm, 100);  
     printf("\nAfter freeing P1 and P3:\n");
     mm_print(mm);

     //mm_coalesce(mm);
     //printf("\nAfter coalescence:\n");
     //mm_print(mm);
 
     mm_destroy(mm);
}

static void demo_stack_history() {
     printf("\n=== Stack (execution history) ===\n");
     Stack* history = stack_create();
     stack_push(history, 1);
     stack_push(history, 2);
     stack_push(history, 3);
     printf("Last executed PID: %d\n", stack_pop(history));
     printf("Before that:       %d\n", stack_pop(history));
     stack_destroy(history);
}

static void demo_finished_list() {
     printf("\n=== Linked List (finished processes by PID) ===\n");
     LinkedList* done = ll_create();
     Process p1 = {3, 5, 0, 2, 100, FINISHED};
     Process p2 = {1, 3, 0, 1, 50,  FINISHED};
     Process p3 = {2, 4, 0, 3, 200, FINISHED};
     ll_insert_sorted(done, p1);
     ll_insert_sorted(done, p2);
     ll_insert_sorted(done, p3);
     ll_print(done);
     ll_destroy(done);
}


int main(int argc, char* argv[]) {
      printf("╔═════════════════════════════════════╗\n");
      printf("║   Mini OS Simulator – Tralaleritos  ║\n");
      printf("╚═════════════════════════════════════╝\n");

      if (argc > 1) {
          int n_processes = atoi(argv[1]);
          printf("[INFO] Modo Benchmark: Simulando %d procesos desde CSV...\n", n_processes);

          timer_start();

          Process* lista_procesos = (Process*)malloc(n_processes * sizeof(Process));

          parser_load_processes("data/inputs/processes.csv", lista_procesos, n_processes);
          
          printf("[OK] Finalizado en: %.2f ms\n", timer_elapsed_ms());
          free(lista_procesos);
          return 0;
      }
     



      timer_start();
     
     demo_stack_history();
     demo_fifo();
     demo_round_robin();
     demo_sjf();
     demo_memory();
     demo_finished_list();

     printf("\nTotal elapsed: %.2f ms\n", timer_elapsed_ms());
     return 0;
}
