#include <stdlib.h>
#include <stdio.h>

// actual length is 7, operator[6] == '\0'
const char operator_list[] = {'+', '-', '*', '/', '(', ')', '#'};

int search(char c) {
    for (int i = 0; i < 7; i++)
        if (c == operator_list[i])
            return i;
    return -1;
}

// find length of type char[]
int len(char *str) {
    int i = 0;
    for (; str[i] != '\0'; i++);
    return i;
}

int validate(char *str, int length) {
    struct {
        char *bottom;
        char *top;
    } buffer;
    buffer.bottom = (char *) malloc(length * sizeof(char));
    buffer.top = buffer.bottom;
    for (int i = 0; i < length; i++) {
        if (str[i] == '(') {
            *(buffer.top++) = '(';
            continue;
        }
        if (str[i] == ')')
            if (*(buffer.top - 1) == '(') {
                buffer.top--;
                continue;
            } else {
                free(buffer.bottom);
                return 0;
            }
        if (search(str[i]) != -1 || (str[i] >= '0' && str[i] <= '9')) {
            // printf("char %c is legal\n", str[i]);
            continue;
        } else {
            // printf("char %c is illegal\n", str[i]);
            free(buffer.bottom);
            return 0;
        }
    }
    free(buffer.bottom);
    return 1;
}

#define GREATER 0
#define EQUAL 1
#define LESS 2
#define END 3

// forward and backward are the indices that chars correspond
int judge_priority(char forward, char backward) { // return backward >, < or = forward
    switch (forward / 2) {
        case 0:
            if (backward == 2 || backward == 3 || backward == 4)
                return GREATER;
            else
                return LESS;
        case 1:
            if (backward == 4)
                return GREATER;
            else
                return LESS;
        case 2:
            if (backward == 5)
                return EQUAL;
            else
                return GREATER;
        case 3:
            if (backward == 6)
                return END;
            else
                return GREATER;
    }
}

double compute(char *expression, int length) {
    if (!validate(expression, length)) {
        printf("illegal expression");
        return 0;
    }
    struct {
        char *bottom;
        char *top;
    } operator;
    operator.bottom = (char *) malloc(length * sizeof(char));
    operator.top = operator.bottom + 1;
    operator.bottom[0] = 6; //init operator stack with a '\0' in the bottom
    struct {
        double *bottom;
        double *top;
    } operand;
    operand.top = operand.bottom = (double *) malloc(length * sizeof(double));
    struct {
        char list[7];
        int top;
    } buffer;
    buffer.top = 0;
    //above init the three stacks
    char current;
    for (int i = 0; i < length; i++) {
        current = expression[i];
        printf("current char: %c\t", current);
        char index = search(current);
        printf("%d\n", index);
        if (index == -1)
            buffer.list[buffer.top++] = current;
        else {
            if (buffer.top != 0) {
                int num = 0;
                int multi = 1;
                while (buffer.top != 0) {
                    num += (buffer.list[--buffer.top] - '0') * multi;
                    multi *= 10;
                }
                *(operand.top++) = num;
                printf("push %f in opd_stack\n", *(operand.top - 1));
            }
            double right;
            double left;
            double result;
            judge:
            printf("%d\t%d\n", *(operator.top - 1), index);
            switch (judge_priority(*(operator.top - 1), index)) {
                case GREATER:
                    printf("greater, push %c in opr_stack\n", operator_list[index]);
                    *(operator.top++) = index;
                    break;
                case EQUAL:
                    printf("estimate ()\n");
                    operator.top--;
                    break;
                case LESS:
                    right = *(--operand.top);
                    left = *(operand.top - 1);
                    switch (*(operator.top - 1)) {
                        case 0: // '+'
                            *(operand.top - 1) = left + right;
                            break;
                        case 1: // '-'
                            *(operand.top - 1) = left - right;
                            break;
                        case 2: // '*'
                            *(operand.top - 1) = left * right;
                            break;
                        case 3: // '/'
                            *(operand.top - 1) = left / right;
                            break;
                    }
                    printf("compute %f%c%f\t%f\n", left, operator_list[*(operator.top - 1)], right, *(operand.top - 1));
                    operator.top--;
                    goto judge;
                case END:
                    printf("return the result\n");
                    result = operand.bottom[0];
                    free(operator.bottom);
                    free(operand.bottom);
                    return result;
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    // char d[] = {'s', 'd'};
    // printf("%d", d[2] == '\0');
    char expression[100];
    scanf("%s", expression);
    int length = len(expression);
    expression[length++] = '#';
    double result = compute(expression, length);
    printf("%f", result);
    return 0;
}
