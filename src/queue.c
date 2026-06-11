#include <stdlib.h>
#include "queue.h"

typedef struct QNode {
     int value;
     struct QNode* next;
} QNode;

struct Queue {
     QNode* front;
     QNode* rear;
     int size;
};


Queue* queue_create() {
     Queue* q = malloc(sizeof(Queue));
     q->front = q->rear = NULL;
     q->size  = 0;
     return q;
}


void enqueue(Queue* q, int value) {
     QNode* n = malloc(sizeof(QNode));
     n->value = value;
     n->next = NULL;
     if (!q->rear) {
         q->front = q->rear = n;
    }else{
         q->rear->next = n;
         q->rear = n;
    }
     q->size++;
}


int dequeue(Queue* q) {
     if (!q->front){
         return -1;
     }
     QNode* tmp = q->front;
     int val = tmp->value;
     q->front = tmp->next;
     if (!q->front){
         q->rear = NULL;
     }
     free(tmp);
     q->size--;
     return val;
}


int queue_peek(Queue* q) {
     if (!q->front){
         return -1;
     }
     return q->front->value;
}


int queue_is_empty(Queue* q) {
     return q->front == NULL;
}


void queue_destroy(Queue* q) {
     while (!queue_is_empty(q)) dequeue(q);
     free(q);
}
