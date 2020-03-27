#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int x;
    int y;
} point;

// value 1 represents blank block, value 0 represents wall
typedef struct {
    int **matrix;
    int row;
    int column;
} maze;

typedef struct {
    point *bottom;
    point *top;
} stack;

void push(stack *stack, point point) {
    *(stack->top++) = point;
}

stack *solution(maze maze, point enter, point exit) {
    maze.matrix[enter.x][enter.y] = 0;
    stack *routine = (stack *) malloc(sizeof(stack));
    routine->bottom = (point *) malloc(maze.row * maze.column * sizeof(point));
    routine->top = routine->bottom;
    point position = {enter.x, enter.y};
    *(routine->top++) = position;
    while (position.x != exit.x || position.y != exit.y) {
        if (maze.matrix[position.x + 1][position.y]) {
            position.x++;
            maze.matrix[position.x][position.y] = 0;
            *(routine->top++) = position;
            continue;
        }
        if (maze.matrix[position.x - 1][position.y]) {
            position.x--;
            maze.matrix[position.x][position.y] = 0;
            *(routine->top++) = position;
            continue;
        }
        if (maze.matrix[position.x][position.y + 1]) {
            position.y++;
            maze.matrix[position.x][position.y] = 0;
            *(routine->top++) = position;
            continue;
        }
        if (maze.matrix[position.x + 1][position.y - 1]) {
            position.y--;
            maze.matrix[position.x][position.y] = 0;
            *(routine->top++) = position;
            continue;
        }
        routine->top--;
    }
    return routine;
}

void print(stack *stack) {
    printf("[(%d,%d)", (*(stack->bottom)).x, (*(stack->bottom)).y);
    for (int i = 1; stack->bottom + i != stack->top; i++)
        printf(",(%d,%d)", (*(stack->bottom + i)).x, (*(stack->bottom + i)).y);
    printf("]");
}
