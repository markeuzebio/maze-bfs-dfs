#ifndef __LINKED_LIST__
#define __LINKED_LIST__

#include <stdbool.h>
#include "node.h"

typedef struct LinkedList {
    Node *first;
    Node *last;
} LinkedList;

typedef LinkedList Queue;
typedef LinkedList Stack;

void initLinkedList(LinkedList *l);
bool isQueueEmpty(Queue *q);
short int enqueueNode(Queue *q, Node *n);
Node *dequeueNode(Queue *q);
void printQueue(Queue *q);
bool isStackEmpty(Stack *s);
short int pushStack(Stack *s, Node *n);
Node *popStack(Stack *s);
void printStack(Stack *s);

#endif