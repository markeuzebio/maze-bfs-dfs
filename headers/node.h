#ifndef __NODE_H__
#define __NODE_H__

#include <stdbool.h>

typedef char Symbol;
typedef struct Maze Maze;

typedef struct Position {
    short int x;
    short int y;
} Position;

typedef struct Data {
    Position position;
    Symbol c;
    bool is_marked;
    bool is_pathway;
} Data;

typedef struct Node {
    Data data;
    struct Node *next;
} Node;

Node* getNode(Maze *m, Position p);
Position getPosition(unsigned short int x, unsigned short int y);
void markNode(Node* n);
void markAsPathway(Node *n);
bool isPositionAvailable(Maze *m, Position p);

#endif