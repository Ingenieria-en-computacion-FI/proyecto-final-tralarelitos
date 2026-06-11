#include <stdlib.h>
#include <stdio.h>
#include "memory_manager.h"

MemoryManager* mm_create(int total_memory) {
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

int mm_allocate_first_fit(MemoryManager* mm, int size) {
     MemoryBlock* cur = mm->head;
     while (cur) {
         if (cur->free && cur->size >= size) {
             if (cur->size > size) {
                 MemoryBlock* rest = malloc(sizeof(MemoryBlock));
                 rest->start = cur->start + size;
                 rest->size  = cur->size  - size;
                 rest->free  = 1;
                 rest->pid   = -1;
                 rest->next  = cur->next;
                 rest->prev  = cur;
                 if (cur->next) cur->next->prev = rest;
                 cur->next   = rest;
             }
             cur->size = size;
             cur->free = 0;
             cur->pid  = size;
             return cur->start;
         }
         cur = cur->next;
     }
     return -1;
}

void mm_free(MemoryManager* mm, int pid) {
     MemoryBlock* cur = mm->head;
     while (cur) {
         if (!cur->free && (cur->pid == pid || cur->size == pid)) {
             cur->free = 1;
             cur->pid  = -1;

             if (cur->next && cur->next->free) {
                 MemoryBlock* next_block = cur->next;
                 cur->size += next_block->size;
                 cur->next = next_block->next;
                 if (next_block->next) next_block->next->prev = cur;
                 free(next_block);
             }

             if (cur->prev && cur->prev->free) {
                 MemoryBlock* prev_block = cur->prev;
                 prev_block->size += cur->size;
                 prev_block->next = cur->next;
                 if (cur->next){
                     cur->next->prev = prev_block;
                 }
                 free(cur);
             }
             return;
         }
         cur = cur->next;
     }
}

void mm_print(MemoryManager* mm) {
     MemoryBlock* cur = mm->head;
     printf("[Memory Map] total=%d\n", mm->total_memory);
     while (cur) {
         printf("  [%d-%d] size=%d %s pid=%d\n",
             cur->start, cur->start + cur->size - 1, cur->size,
             cur->free ? "FREE" : "USED", cur->pid
         );
         cur = cur->next;
     }
}

void mm_destroy(MemoryManager* mm) {
     MemoryBlock* cur = mm->head;
     while (cur) {
         MemoryBlock* tmp = cur->next;
         free(cur);
         cur = tmp;
     }
     free(mm);
}