//
// Created by cyb12 on 2020/3/21.
//
#include <cstdio>
#include <cstdlib>
#include <string>

int fibonacci_ruc(int n) {
    if (n == 1 || n == 2)
        return 1;
    else {
        int a = fibonacci_ruc(n - 1);
        int b = fibonacci_ruc(n - 2);
        return a + b;
    }
}

int fibonacci_stk(int n) {
    if (n == 1 || n == 2) {//trivial cases
        return 1;
    }
    struct frame {
        int i;//parameters
        int para[2];//local variables
        int status;//return position
    };
    frame *stack = (frame *) malloc(n * sizeof(frame));
    int cur = 0;
    stack[cur++] = {n, 0};
    frame *top;
    while (cur) {
        top = stack + cur - 1;
        if (top->status != 2) {
            top->status++;
            int i = top->i - top->status;
            if (i > 2)//push new frame into stack
                stack[cur++] = {i, 0};
            else//reach trivial condition
                top->para[top->status - 1] = 1;
        } else if (cur == 1) {//reach an end
            break;
        } else {//pop from stack
            int returnValue = top->para[0] + top->para[1];
            frame *prev = top - 1;
            prev->para[prev->status - 1] = returnValue;
            cur--;
        }
    }
    int result = stack->para[0] + stack->para[1];
    free(stack);
    return result;
}

int main(int argc, char const *argv[]) {
    int times = 20;
    for (int i = 1; i < times; ++i) {
        printf("%d ", fibonacci_ruc(i));
    }
    printf("\n");
    for (int i = 1; i < times; ++i) {
        printf("%d ", fibonacci_stk(i));
    }
    return 0;
}
