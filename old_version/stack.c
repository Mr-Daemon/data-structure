#include <stdlib.h>
#include <stdio.h>

#define INIT_STACK_SIZE 100
#define STACK_SIZE_INCREMENT 10

typedef struct {
    char *bottom;
    char *top;
    int size;
} stack;

stack *initStack() {
    stack *newStack = (stack *) malloc(sizeof(stack));
    newStack->size = INIT_STACK_SIZE;
    newStack->bottom = (char *) malloc(INIT_STACK_SIZE * sizeof(char));
    newStack->top = newStack->bottom;
}

void push(stack *stack, char c) {
    if (stack->top - stack->bottom >= stack->size) {
        stack->size += STACK_SIZE_INCREMENT;
        stack->bottom = (char *) realloc(stack->bottom, stack->size * sizeof(char));
    }
    *(stack->top++) = c;
}

char pop(stack *stack) {
    if (stack->top == stack->bottom)
        return '\0';
    char c = *(--stack->top);
    if (stack->size > INIT_STACK_SIZE && (stack->size - (stack->top - stack->bottom) >= STACK_SIZE_INCREMENT)) {
        stack->size -= STACK_SIZE_INCREMENT;
        stack->bottom = (char *) realloc(stack->bottom, stack->size * sizeof(char));
    }
    return c;
}

char getTop(stack *stack) {
    if (stack->top == stack->bottom)
        return '\0';
    return *(stack->top - 1);
}

void print(stack *stack) {
    printf("[%c", *(stack->bottom));
    int i = 1;
    while (*(stack->bottom + i) != *(stack->top)) {
        printf(",%c", *(stack->bottom + i));
        i++;
    }
    printf("]");
}

void destory(stack *stack) {
    free(stack->bottom);
    free(stack);
}

void clear(stack *stack) {
    stack->top = stack->bottom;
    stack->bottom = (char *) realloc(stack->bottom, INIT_STACK_SIZE * sizeof(char));
    stack->size = INIT_STACK_SIZE;
}

void decToOct() {
    int *input;
    scanf("%d", input);
    int decimal = *input;
    stack *buffer = initStack();
    while (decimal) {
        push(buffer, (char) (decimal % 8 + 48));
        // printf("%d\t%d\t%c\n", decimal, (decimal % 8), (char)(decimal % 8 + 48));
        decimal = decimal / 8;
    }
    char c = pop(buffer);
    printf("0");
    while (c) {
        printf("%c", c);
        c = pop(buffer);
    }
    destory(buffer);
}

int validate(char *c_str, int length) {
    stack *buffer = initStack();
    for (int i = 0; i < length; i++) {
        char c = c_str[i];
        if (c == '(' || c == '{')
            push(buffer, c);
        if (c == ')')
            if (getTop(buffer) == '(')
                pop(buffer);
            else {
                destory(buffer);
                return 0;
            }
        if (c == '}')
            if (getTop(buffer) == '{')
                pop(buffer);
            else {
                destory(buffer);
                return 0;
            }
    }
    destory(buffer);
    return 1;
}

int main(int argc, char const *argv[]) {
    // stack *myStack = initStack();
    // push(myStack, 'a');
    // push(myStack, 'b');
    // push(myStack, 'c');
    // push(myStack, 'd');
    // print(myStack);
    // decToOct();
    printf("%d", validate("{(bjkj)}", 4));
    return 0;
}
