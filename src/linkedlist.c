#include <stdio.h>
#include <stdlib.h>

#include "../headers/linkedlist.h"

bool isQueueEmpty(Queue *q) {
    return q->first == NULL;
}

bool isStackEmpty(Stack *s) {
    return s->first == NULL;
}

short int enqueueNode(Queue *q, Node *n) {
    if(isQueueEmpty(q)) {
        q->first = q->last = n;
    }
    else {
        q->last->next = n;
        q->last = n;
    }

    return 1;
}

short int pushStack(Stack *s, Node *n) {
    Node *aux;

    if(isStackEmpty(s)) {
        s->first = s->last = n;
    } else {
        aux = s->first;
        s->first = n;
        n->next = aux;
    }

    return 1;
}

Node *dequeueNode(Queue *q) {
    Node *aux;

    if(isQueueEmpty(q))
        return NULL;

    aux = q->first;

    q->first = q->first->next;

    return aux;
}

Node *popStack(Stack *s) {
    Node *aux;

    if(isStackEmpty(s))
        return NULL;

    aux = s->first;

    s->first = s->first->next;

    return aux;
}

void printQueue(Queue *q) {
    Node *n = q->first;

    while(n != NULL) {
        printf("(%d, %d)\n", n->data.position.x, n->data.position.y);
        n = n->next;
    }
}

void printStack(Stack *s) {
    Node *n = s->first;

    while(n != NULL) {
        printf("(%d, %d)\n", n->data.position.x, n->data.position.y);
        n = n->next;
    }
}

void initLinkedList(LinkedList *l) {
    l->first = l->last = NULL;
}