#include <stdio.h>
#include "../headers/dfs.h"
#include "../headers/linkedlist.h"
#include "../headers/node.h"
#include "../headers/maze.h"

// PRECEDENCE ORDER: UP, RIGHT, BOTTOM, LEFT
int DFS(Maze *m, Stack *s) {
    Node *actual_node;
    Position actual_position;
    Position next_position;

    actual_node = popStack(s);

    if(actual_node == NULL)
        return -1;

    actual_position = actual_node->data.position;
    markNode(actual_node);

    // If it found an exit
    if(actual_node->data.c == 's') {
        markAsPathway(actual_node);
        return 1;
    }

    next_position = getPosition(actual_position.x - 1, actual_position.y);
    if(isPositionAvailable(m, next_position)) {
        pushStack(s, getNode(m, next_position));

        if(DFS(m, s) == 1) {
            markAsPathway(actual_node);
            return 1;
        }
    }

    next_position = getPosition(actual_position.x, actual_position.y + 1);
    if(isPositionAvailable(m, next_position)) {
        pushStack(s, getNode(m, next_position));

        if(DFS(m, s) == 1) {
            markAsPathway(actual_node);
            return 1;
        }
    }

    next_position = getPosition(actual_position.x + 1, actual_position.y);
    if(isPositionAvailable(m, next_position)) {
        pushStack(s, getNode(m, next_position));
        
        if(DFS(m, s) == 1) {
            markAsPathway(actual_node);
            return 1;
        }
    }

    next_position = getPosition(actual_position.x, actual_position.y - 1);
    if(isPositionAvailable(m, next_position)) {
        pushStack(s, getNode(m, next_position));
        
        if(DFS(m, s) == 1) {
            markAsPathway(actual_node);
            return 1;
        }
    }

    return -1;
}

int solveMazeDFS(Maze *m) {
    Stack s;
    Position initial_position;

    initLinkedList(&s);
    initial_position = findInitialPosition(m);
    
    if(initial_position.x == -1 || initial_position.y == -1)
        return -2;

    pushStack(&s, getNode(m, initial_position));

    return DFS(m, &s);
}