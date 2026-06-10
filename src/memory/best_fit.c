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