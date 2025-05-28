#include <stdio.h>
#include <stdlib.h>
#include "../headers/maze.h"

int initMaze(Maze *maze, unsigned short int size, char **draw) {
    maze->nodes = (Node**) malloc(size * sizeof(Node*));

    if(maze->nodes == NULL)
        return -1;

    for(int i = 0 ; i < size ; i++) {
        maze->nodes[i] = (Node*) malloc(size * sizeof(Node));

        if(maze->nodes[i] == NULL)
            return -1;
    }

    for(int i = 0 ; i < size ; i++) {
        for(int j = 0 ; j < size ; j++) {
            Node *node = &(maze->nodes[i][j]);

            node->next = NULL;
            node->data.is_marked = false;
            node->data.is_pathway = false;
            node->data.position.x = i;
            node->data.position.y = j;
            node->data.c = draw[i][j];
        }
    }

    maze->size = size;

    return 1;
}

void finishMaze(Maze *maze) {
    for(int i = 0 ; i < maze->size ; i++)
        free(maze->nodes[i]);

    free(maze->nodes);
}

void printMaze(Maze *m) {
    printf("\n");

    for(int i = 0 ; i < m->size ; i++) {
        for(int j = 0 ; j < m->size ; j++)
            printf("%c", m->nodes[i][j].data.c);

        printf("\n");
    }

    printf("\n");
}

Position findInitialPosition(Maze *maze) {
    Position p;
    p.x = p.y = -1;

    for(int i = 0 ; i < maze->size ; i++)
        for(int j = 0 ; j < maze->size ; j++)
            if(maze->nodes[i][j].data.c == 'g')
                return maze->nodes[i][j].data.position;

    return p;
}

Position findFinalPosition(Maze *maze) {
    Position p;
    p.x = p.y = -1;

    for(int i = 0 ; i < maze->size ; i++)
        for(int j = 0 ; j < maze->size ; j++)
            if(maze->nodes[i][j].data.c == 's')
                return maze->nodes[i][j].data.position;

    return p;
}


void traceMazePathway(Maze *maze) {
    for(int i = 0 ; i < maze->size ; i++)
        for(int j = 0 ; j < maze->size ; j++)
            if(maze->nodes[i][j].data.is_pathway)
                if(maze->nodes[i][j].data.c != 'g' && maze->nodes[i][j].data.c != 's')
                    maze->nodes[i][j].data.c = '.';
}