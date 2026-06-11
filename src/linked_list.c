#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"


LinkedList* ll_create() {
     LinkedList* l = malloc(sizeof(LinkedList));
     l->head = NULL;
     l->size = 0;
     return l;
}


void ll_insert_sorted(LinkedList* l, Process p) {
     LLNode* n = malloc(sizeof(LLNode));
     n->process = p;
     n->next    = NULL;

     if (!l->head || l->head->process.pid >= p.pid) {
         n->next  = l->head;
         l->head  = n;
    } else {
         LLNode* cur = l->head;
         while (cur->next && cur->next->process.pid < p.pid)
             cur = cur->next;
         n->next = cur->next;
         cur->next = n;
    }
     l->size++;
}


Process* ll_find(LinkedList* l, int pid) {
     LLNode* cur = l->head;
     while (cur) {
         if (cur->process.pid == pid){
             return &cur->process;
         }
         cur = cur->next;
    }
     return NULL;
}


void ll_remove(LinkedList* l, int pid) {
     LLNode* cur  = l->head;
     LLNode* prev = NULL;
     while (cur) {
         if (cur->process.pid == pid) {
             if (prev){
                 prev->next = cur->next;
             }else{
                 l->head   = cur->next;
             }
             free(cur);
             l->size--;
             return;
        }
         prev = cur;
         cur  = cur->next;
    }
}


void ll_print(LinkedList* l) {
     LLNode* cur = l->head;
     printf("[Finished processes ordered by PID]\n");
     while (cur) {
         printf("  PID=%d burst=%d priority=%d\n",
                 cur->process.pid,
                 cur->process.burst_time,
                 cur->process.priority);
         cur = cur->next;
    }
}


void ll_destroy(LinkedList* l) {
     LLNode* cur = l->head;
     while (cur) {
         LLNode* tmp = cur->next;
         free(cur);
         cur = tmp;
    }
     free(l);
}
