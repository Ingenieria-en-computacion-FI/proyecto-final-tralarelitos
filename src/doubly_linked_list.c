#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list.h"


DoublyLinkedList* dll_create() {
     DoublyLinkedList* dll = malloc(sizeof(DoublyLinkedList));
     dll->head = dll->tail = NULL;
     dll->size = 0;
     return dll;
}

static DLLNode* new_node(int value) {
     DLLNode* n = malloc(sizeof(DLLNode));
     n->value = value;
     n->next  = n->prev = NULL;
     return n;
}


void dll_push_back(DoublyLinkedList* dll, int value) {
     DLLNode* n = new_node(value);
     if (!dll->tail) {
         dll->head = dll->tail = n;
    } else {
         n->prev = dll->tail;
         dll->tail->next = n;
         dll->tail = n;
    }
     dll->size++;
}


void dll_push_front(DoublyLinkedList* dll, int value) {
     DLLNode* n = new_node(value);
     if (!dll->head) {
         dll->head = dll->tail = n;
    } else {
         n->next = dll->head;
         dll->head->prev = n;
         dll->head = n;
    }
     dll->size++;
}


int dll_pop_back(DoublyLinkedList* dll) {
     if (!dll->tail){
         return -1;
     }
     int val = dll->tail->value;
     DLLNode* tmp = dll->tail;
     dll->tail = dll->tail->prev;
     if (dll->tail){
         dll->tail->next = NULL;
    }else{
         dll->head = NULL;
    }
     free(tmp);
     dll->size--;
     return val;
}


int dll_pop_front(DoublyLinkedList* dll) {
     if (!dll->head){
         return -1;
     }
     int val = dll->head->value;
     DLLNode* tmp = dll->head;
     dll->head = dll->head->next;
     if (dll->head){
         dll->head->prev = NULL;
     }else{
         dll->tail = NULL;
     }
     free(tmp);
     dll->size--;
     return val;
}


void dll_remove_node(DoublyLinkedList* dll, DLLNode* node) {
     if (!node) return;
     if (node->prev){
         node->prev->next = node->next;
     }else{
         dll->head = node->next;
     }
     if (node->next){
         node->next->prev = node->prev;
     }else{
         dll->tail = node->prev;
     }
     free(node);
     dll->size--;
}


DLLNode* dll_find(DoublyLinkedList* dll, int value) {
     DLLNode* cur = dll->head;
     while (cur) {
         if (cur->value == value){
             return cur;
         }
         cur = cur->next;
    }
     return NULL;
}


void dll_print_forward(DoublyLinkedList* dll) {
     DLLNode* cur = dll->head;
     printf("DLL (forward): ");
     while (cur) { printf("%d ", cur->value); cur = cur->next; }
     printf("\n");
}


void dll_print_backward(DoublyLinkedList* dll) {
     DLLNode* cur = dll->tail;
     printf("DLL (backward): ");
     while (cur) { printf("%d ", cur->value); cur = cur->prev; }
     printf("\n");
}


void dll_destroy(DoublyLinkedList* dll) {
     while (dll->head) dll_pop_front(dll);
     free(dll);
}
