#include <stdlib.h>
#include <stdio.h>

typedef struct polynomial {
    int coefficient;
    int exponent;
    struct polynomial *next;
} hNode, *term;

term createTerm(int coefficient, int exponent) {
    term newTerm = (term) malloc(sizeof(hNode));
    newTerm->coefficient = coefficient;
    newTerm->exponent = exponent;
    return newTerm;
}

void addTerm(hNode *head, term newTerm) {
    int coefficient = newTerm->coefficient;
    int exponent = newTerm->exponent;
    if (coefficient == 0)
        return;
    while (head->next) {
        if (head->next->exponent > exponent) {
            newTerm->next = head->next;
            head->next = newTerm;
            return;
        }
        if (head->next->exponent == exponent) {
            head->next->coefficient += coefficient;
            free(newTerm);
            return;
        }
        head = head->next;
    }
    newTerm->next = head->next;
    head->next = newTerm;
}

void destory(hNode *head) {
    while (head->next) {
        term term = head->next->next;
        free(head->next);
        head->next = term;
    }
}

void print(hNode *head) {
    head = head->next;
    printf("%dx^%d", head->coefficient, head->exponent);
    while (head->next) {
        head = head->next;
        printf("+%dx^%d", head->coefficient, head->exponent);
    }
    printf("\n");
}

void add(hNode *a, hNode *b) {
    while (b->next) {
        b = b->next;
        addTerm(a, b);
    }
    destory(b);
}

void multiply(hNode *a, hNode *b) {
    hNode head;
    head.next = NULL;
    term aHead = a;
    term bHead = b;
    while (a->next) {
        a = a->next;
        while (b->next) {
            b = b->next;
            addTerm(&head, createTerm((a->coefficient) * (b->coefficient), (a->exponent) + (b->exponent)));
            printf("add (%d,%d)\n", (a->coefficient) * (b->coefficient), (a->exponent) + (b->exponent));
        }
        b = bHead;
    }
    destory(aHead);
    destory(bHead);
    aHead->next = head.next;
}

int main(int argc, char const *argv[]) {
    hNode head;
    head.next = NULL;
    hNode head1;
    head1.next = NULL;
    addTerm(&head, createTerm(1, 0));
    addTerm(&head, createTerm(1, 3));
    addTerm(&head, createTerm(1, 5));
    addTerm(&head, createTerm(1, 3));
    addTerm(&head, createTerm(1, 2));
    addTerm(&head1, createTerm(1, 0));
    addTerm(&head1, createTerm(1, 3));
    addTerm(&head1, createTerm(1, 5));
    addTerm(&head1, createTerm(1, 3));
    addTerm(&head1, createTerm(1, 2));
    print(&head);
    // destory(&head);
    // addTerm(&head, createTerm(1, 3));
    multiply(&head, &head1);
    print(&head);
    return 0;
}
