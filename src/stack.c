#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct Node {
     int value;
     struct Node* next;
} Node;

struct Stack {
     Node* top;
     int size;
};


Stack* stack_create() {
     Stack* s = malloc(sizeof(Stack));
     s->top = NULL;
     s->size = 0;
    return s;
}


void stack_push(Stack* s, int value) {
     Node* n = malloc(sizeof(Node));
     n->value = value;
     n->next = s->top;
     s->top = n;
     s->size++;
}


int stack_pop(Stack* s) {
      if (!s->top){ 
           return -1;
     }
      Node* tmp = s->top;
      int val = tmp->value;
      s->top = tmp->next;
      free(tmp);
      s->size--;
      return val;
}


int stack_peek(Stack* s) {
      if (!s->top){
           return -1;
     }
      return s->top->value;
}

int stack_is_empty(Stack* s) {
      return s->top == NULL;
}

void stack_destroy(Stack* s) {
      while (!stack_is_empty(s)){
           stack_pop(s);
     }
      free(s);
}
