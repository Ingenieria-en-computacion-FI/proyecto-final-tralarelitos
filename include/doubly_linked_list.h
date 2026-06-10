#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

typedef struct DLLNode {
    int value;
    struct DLLNode* next;
    struct DLLNode* prev;
} DLLNode;

typedef struct DoublyLinkedList {
    DLLNode* head;
    DLLNode* tail;
    int size;
} DoublyLinkedList;

DoublyLinkedList* dll_create();
void     dll_push_back(DoublyLinkedList* dll, int value);
void     dll_push_front(DoublyLinkedList* dll, int value);
int      dll_pop_back(DoublyLinkedList* dll);
int      dll_pop_front(DoublyLinkedList* dll);
void     dll_remove_node(DoublyLinkedList* dll, DLLNode* node);
DLLNode* dll_find(DoublyLinkedList* dll, int value);
void     dll_print_forward(DoublyLinkedList* dll);
void     dll_print_backward(DoublyLinkedList* dll);
void     dll_destroy(DoublyLinkedList* dll);

#endif
