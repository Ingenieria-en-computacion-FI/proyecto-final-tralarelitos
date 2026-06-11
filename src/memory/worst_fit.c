#include <stdlib.h>
#include <stdio.h>
#include "memory_manager.h"


int mm_allocate_worst_fit(
     MemoryManager* mm,
     int size
){
     MemoryBlock* worst = NULL;
     MemoryBlock* cur   = mm->head;
     while (cur) {
         if (cur->free && cur->size >= size) {
             if (!worst || cur->size > worst->size) worst = cur;
        }
         cur = cur->next;
    }
     if (!worst) return -1;

     if (worst->size > size) {
         MemoryBlock* rest = malloc(sizeof(MemoryBlock));
         rest->start = worst->start + size;
         rest->size  = worst->size  - size;
         rest->free  = 1;
         rest->pid   = -1;
         rest->next  = worst->next;
         rest->prev  = worst;
         if (worst->next) worst->next->prev = rest;
         worst->next  = rest;
    }
     worst->size = size;
     worst->free = 0;
     worst->pid  = size;
     return worst->start;
}

