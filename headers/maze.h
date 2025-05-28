#ifndef __MAZE_H__
#define __MAZE_H__

#include "linkedlist.h"

typedef struct Maze {
    Node **nodes;
    unsigned short int size;
} Maze;

int initMaze(Maze *maze, unsigned short int size, char **draw);
void finishMaze(Maze *maze);
void printMaze(Maze *maze);
Position findInitialPosition(Maze *maze);
Position findFinalPosition(Maze *maze);
void traceMazePathway(Maze *maze);

#endif