#include <stdlib.h>
#include <stdio.h>
#include "memory_manager.h"


MemoryManager* mm_create(
     int total_memory
){
     MemoryManager* mm = malloc(sizeof(MemoryManager));
     mm->total_memory  = total_memory;

     MemoryBlock* b = malloc(sizeof(MemoryBlock));
     b->start = 0;
     b->size  = total_memory;
     b->free  = 1;
     b->pid   = -1;
     b->next  = NULL;
     b->prev  = NULL;

     mm->head = b;
     return mm;
}

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

void mm_free(
     MemoryManager* mm, 
     int pid
){
     MemoryBlock* cur = mm->head;
     while (cur) {
         if (!cur->free && cur->pid == pid) {
             cur->free = 1;
             cur->pid  = -1;
             return;
        }
         cur = cur->next;
    }
}

void mm_print(
     MemoryManager* mm
){
     MemoryBlock* cur = mm->head;
     printf("[Memory Map] total=%d\n", mm->total_memory);
     while (cur) {
         printf("  [%d-%d] size=%d %s pid=%d\n",
             cur->start, 
             cur->start + cur->size - 1,
             cur->size,
             cur->free ? "FREE" : "USED",
             cur->pid
        );
         cur = cur->next;
    }
}


void mm_destroy(
     MemoryManager* mm
){
     MemoryBlock* cur = mm->head;
     while (cur) {
         MemoryBlock* tmp = cur->next;
         free(cur);
         cur = tmp;
    }
     free(mm);
}
