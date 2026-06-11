#include <stdlib.h>
#include <stdio.h>
#include "memory_manager.h"


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
