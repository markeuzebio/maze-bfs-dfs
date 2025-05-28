#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "headers/linkedlist.h"
#include "headers/maze.h"
#include "headers/dfs.h"
#include "headers/bfs.h"

#define BUFF_SIZE 1024

int checkArgs(int argc, char *argv[]) {
    FILE *param;

    if(argc != 2)
        return -1;
    
    param = fopen(argv[1], "r");

    if(param == NULL)
        return -2;

    fclose(param);

    return 1;
}

char **allocDraw(unsigned int size) {
    char **draw = (char**) malloc(size * sizeof(char*));

    if(draw == NULL)
        return NULL;

    for(unsigned int i = 0 ; i < size ; i++) {
        draw[i] = (char*) malloc(size * sizeof(char) + sizeof(char)); // It takes '\0' into account

        if(draw[i] == NULL)
            return NULL;
    }

    return draw;
}

void deallocDraw(char ***draw, unsigned int size) {
    for(unsigned int i = 0 ; i < size ; i++)
        free((*draw)[i]);

    free(*draw);
}

int readContent(char *file_name, char ***draw, unsigned int *size) {
    char buffer[BUFF_SIZE];
    FILE *f = fopen(file_name, "r");

    if(f == NULL)
        return -1;

    if(fgets(buffer, sizeof(buffer), f) == NULL)
        return -1;

    if(sscanf(buffer, "%u", size) != 1)
        return -2;

    *draw = allocDraw(*size);

    for(unsigned int i = 0 ; i < *size ; i++) {
        fgets(buffer, sizeof(buffer), f);
        sscanf(buffer, "%[^\n]s", (*draw)[i]);
    }

    fclose(f);

    return 1;
}

int main(int argc, char *argv[]) {
    Maze m;
    char **draw;
    char option;
    unsigned int size;
    int status;

    if(checkArgs(argc, argv) != 1) {
        printf("Erro de parametrização. Abortando o programa...\n");
        exit(1);
    }

    if(readContent(argv[1], &draw, &size) != 1)
        exit(-1);

    if(initMaze(&m, size, draw) != 1)
        exit(-1);

    deallocDraw(&draw, size);

    printf("Escolha entre BFS (b) e DFS (d): "); scanf("%c", &option);
    option = tolower(option);

    switch(option) {
        case 'b':
            status = solveMazeBFS(&m);

	    if(status == 1) {
            	traceMazePathway(&m);
		printMaze(&m);
	    }
	    else if(status == -1) {
		printf("\nO labirinto informado não possui solução!\n");
	    }
            break;
        case 'd':
            status = solveMazeDFS(&m);

	    if(status == 1) {
            	traceMazePathway(&m);
                printMaze(&m);
	    }
	    else if(status == -1) {
                printf("\nO labirinto informado não possui solução!\n");
	    }
            break;
        default:
            printf("OPÇÃO INVÁLIDA! ABORTANDO O PROGRAMA...\n");
            exit(-2);
            break;
    }

    finishMaze(&m);

    return 0;
}
