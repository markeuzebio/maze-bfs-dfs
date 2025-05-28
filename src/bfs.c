#include <stdio.h>
#include <stdlib.h>
#include "../headers/bfs.h"
#include "../headers/maze.h"
#include "../headers/linkedlist.h"
#include "../headers/node.h"

Position** allocatePrecedenceMatrix(unsigned short int size) {
    Position** p_matrix = (Position**) malloc(size * sizeof(Position*));

    if(p_matrix == NULL)
        return NULL;

    for(int i = 0 ; i < size ; i++) {
        p_matrix[i] = (Position*) malloc(size * sizeof(Position*));

        if(p_matrix[i] == NULL) {
            for(int j = i - 1 ; j >= 0 ; j--)
                free(p_matrix[j]);

            return NULL;
        }
    }

    return p_matrix;
}

void deallocatePrecedenceMatrix(Position ***p, unsigned short int size) {
    for(unsigned short int i = 0 ; i < size ; i++)
        free((*p)[i]);

    free(*p);
}

int BFS(Maze *m, Queue *q, Position **precedence_matrix) {
    Node *actual_node;
    Position actual_position;
    Position next_position;

    actual_node = dequeueNode(q);

    // It means there is no path
    if(actual_node == NULL)
        return -1;

    actual_position = actual_node->data.position;
    markNode(actual_node);

    // If it found an exit
    if(actual_node->data.c == 's')
        return 1;

    next_position = getPosition(actual_position.x - 1, actual_position.y);
    if(isPositionAvailable(m, next_position)) {
        enqueueNode(q, getNode(m, next_position));
        markNode(getNode(m, next_position));
        precedence_matrix[next_position.x][next_position.y] = actual_position;
    }

    next_position = getPosition(actual_position.x, actual_position.y + 1);
    if(isPositionAvailable(m, next_position)) {
        enqueueNode(q, getNode(m, next_position));
        markNode(getNode(m, next_position));
        precedence_matrix[next_position.x][next_position.y] = actual_position;
    }

    next_position = getPosition(actual_position.x + 1, actual_position.y);
    if(isPositionAvailable(m, next_position)) {
        enqueueNode(q, getNode(m, next_position));
        markNode(getNode(m, next_position));
        precedence_matrix[next_position.x][next_position.y] = actual_position;
    }

    next_position = getPosition(actual_position.x, actual_position.y - 1);
    if(isPositionAvailable(m, next_position)) {
        enqueueNode(q, getNode(m, next_position));
        markNode(getNode(m, next_position));
        precedence_matrix[next_position.x][next_position.y] = actual_position;
    }

    return BFS(m, q, precedence_matrix);

    return -1;
}

void markPathWay(Maze *m, Position **precedence_matrix) {
    Position initial_position = findInitialPosition(m);
    Position aux = findFinalPosition(m);

    while(initial_position.x != aux.x || initial_position.y != aux.y) {
        m->nodes[aux.x][aux.y].data.is_pathway = true;
        aux = precedence_matrix[aux.x][aux.y];
    }
}

int solveMazeBFS(Maze *m) {
    Queue q;
    Position initial_position;
    Position **precedence_matrix = allocatePrecedenceMatrix(m->size);

    initLinkedList(&q);
    initial_position = findInitialPosition(m);
    precedence_matrix[initial_position.x][initial_position.y] = initial_position;

    if(initial_position.x == -1 || initial_position.y == -1)
        return -2;
    else if(precedence_matrix == NULL)
        return -3;

    enqueueNode(&q, getNode(m, initial_position));

    if(BFS(m, &q, precedence_matrix) == 1) {
        markPathWay(m, precedence_matrix);
        deallocatePrecedenceMatrix(&precedence_matrix, m->size);
        return 1;
    }

    deallocatePrecedenceMatrix(&precedence_matrix, m->size);

    return -1;
}