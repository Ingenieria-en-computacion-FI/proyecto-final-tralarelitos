#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "process.h"

typedef struct LLNode {
     Process process;
     struct LLNode* next;
} LLNode;

typedef struct LinkedList {
     LLNode* head;
     int size;
} LinkedList;

LinkedList* ll_create();

void ll_insert_sorted(
     LinkedList* list,
     Process p
);

Process* ll_find(
     LinkedList* list,
     int pid
);

void ll_remove(
     LinkedList* list, 
     int pid
);

void ll_print(
     LinkedList* list
);

void ll_destroy(
     LinkedList* list
);

#endif