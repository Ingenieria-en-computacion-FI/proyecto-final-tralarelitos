#include <stdlib.h>
#include "circular_queue.h"

struct CircularQueue {
     int* buffer;
     int  capacity;
     int  head;
     int  tail;
     int  size;
};


CircularQueue* cq_create(int capacity) {
     CircularQueue* cq = malloc(sizeof(CircularQueue));
     cq->buffer = malloc(sizeof(int) * capacity);
     cq->capacity = capacity;
     cq->head = 0;
     cq->tail = 0;
     cq->size = 0;
     return cq;
}


void cq_enqueue(CircularQueue* cq, int value) {
     if (cq_is_full(cq)) {
         int  new_cap = cq->capacity * 2;
         int* buf = malloc(sizeof(int) * new_cap);
         for (int i = 0; i < cq->size; i++){
             buf[i] = cq->buffer[(cq->head + i) % cq->capacity];
         }
         free(cq->buffer);
         cq->buffer = buf;
         cq->head = 0;
         cq->tail = cq->size;
         cq->capacity = new_cap;
    }
     cq->buffer[cq->tail] = value;
     cq->tail = (cq->tail + 1) % cq->capacity;
     cq->size++;
}


int cq_dequeue(CircularQueue* cq) {
     if (cq_is_empty(cq)){
         return -1;
     }
     int val = cq->buffer[cq->head];
     cq->head = (cq->head + 1) % cq->capacity;
     cq->size--;
     return val;
}


int cq_peek(CircularQueue* cq) {
     if (cq_is_empty(cq)){
         return -1;
     }
     return cq->buffer[cq->head];
}

int cq_is_empty(CircularQueue* cq){
     return cq->size == 0; 
}
int cq_is_full(CircularQueue* cq){ 
     return cq->size == cq->capacity; 
}
int cq_size(CircularQueue* cq){ 
     return cq->size; 
}


void cq_destroy(CircularQueue* cq) {
     free(cq->buffer);
     free(cq);
}
