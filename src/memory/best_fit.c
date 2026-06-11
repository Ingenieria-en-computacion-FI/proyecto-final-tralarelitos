#include <stdlib.h>
#include <stdio.h>
#include "memory_manager.h"

int mm_allocate_best_fit(
     MemoryManager* mm, 
     int size
){
     MemoryBlock* best = NULL;
     MemoryBlock* cur  = mm->head;
     while (cur) {
         if (cur->free && cur->size >= size) {
             if (!best || cur->size < best->size) best = cur;
        }
         cur = cur->next;
    }
     if (!best) {
         return -1;
    }
    if (best->size > size) {
         MemoryBlock* rest = malloc(sizeof(MemoryBlock));
         rest->start = best->start + size;
         rest->size = best->size  - size;
         rest->free = 1;
         rest->pid = -1;
         rest->next = best->next;
         rest->prev = best;
         if (best->next) best->next->prev = rest;
         best->next = rest;
    }
     best->size = size;
     best->free = 0;
     best->pid  = size;
     return best->start;
}

