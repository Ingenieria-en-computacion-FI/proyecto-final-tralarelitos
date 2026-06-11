#include <stdlib.h>
#include <stdio.h>
#include "memory_manager.h"


void mm_coalesce(
     MemoryManager* mm
){
     MemoryBlock* cur = mm->head;
     while (cur && cur->next) {
         if (cur->free && cur->next->free) {
             MemoryBlock* nxt = cur->next;
             cur->size += nxt->size;
             cur->next = nxt->next;
             if (nxt->next) nxt->next->prev = cur;
             free(nxt);
        } else {
             cur = cur->next;
        }
    }
}
