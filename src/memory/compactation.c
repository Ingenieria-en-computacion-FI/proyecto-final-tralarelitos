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

void mm_compact(
     MemoryManager* mm
){
     int offset = 0;
     MemoryBlock* cur = mm->head;
     while (cur) {
         if (!cur->free) {
             cur->start = offset;
             offset += cur->size;
        }
         cur = cur->next;
    }
     MemoryBlock* prev_used = NULL;
     cur = mm->head;
     MemoryBlock* new_head = NULL;
     MemoryBlock* tail = NULL;

     while (cur) {
         MemoryBlock* nxt = cur->next;
         if (!cur->free) {
             cur->next = NULL;
             cur->prev = tail;
             if (tail) tail->next = cur;
             else new_head = cur;
             tail = cur;
        } else {
             free(cur);
        }
         cur = nxt;
    }
     (void)prev_used;

     if (offset < mm->total_memory) {
         MemoryBlock* free_blk = malloc(sizeof(MemoryBlock));
         free_blk->start = offset;
         free_blk->size  = mm->total_memory - offset;
         free_blk->free  = 1;
         free_blk->pid   = -1;
         free_blk->next  = NULL;
         free_blk->prev  = tail;
         if (tail) tail->next = free_blk;
         else new_head = free_blk;
    }
     mm->head = new_head;
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