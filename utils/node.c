#include "../headers/node.h"
#include "../headers/maze.h"

Node* getNode(Maze *m, Position p) {
    return &(m->nodes[p.x][p.y]);
}

Position getPosition(unsigned short int x, unsigned short int y) {
    Position p;

    p.x = x;
    p.y = y;

    return p;
}

void markNode(Node* n) {
    n->data.is_marked = true;
}

void markAsPathway(Node *n) {
    n->data.is_pathway = true;
}

bool isPositionAvailable(Maze *m, Position p) {
    if(p.x >= m->size || p.x < 0)
        return false;
    else if(p.y >= m->size || p.y < 0)
        return false;
    else if(getNode(m, p)->data.is_marked)
        return false;
    else if(getNode(m, p)->data.c != ' ' && getNode(m, p)->data.c != 's')
        return false;

    return true;
}