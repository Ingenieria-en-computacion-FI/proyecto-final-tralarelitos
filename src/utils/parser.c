#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "process.h"


int parser_load_processes(const char* filepath, Process* out, int max) {
     FILE* f = fopen(filepath, "r");
     if (!f){
         fprintf(stderr, "Cannot open %s\n", filepath); 
         return 0; 
    }

     int count = 0;
     char line[256];
     fgets(line, sizeof(line), f);

     while (fgets(line, sizeof(line), f) && count < max) {
         Process p;
         if (sscanf(line, "%d,%d,%d,%d", &p.pid, &p.burst_time, &p.priority, &p.memory_required) == 4) {
             p.remaining_time = p.burst_time;
             p.state = READY;
             out[count++] = p;
        }
    }
     fclose(f);
     return count;
}
