//
// Created by cyb12 on 2020-02-03.
//

#ifndef ALGORITHM_EXPRESSION_H
#define ALGORITHM_EXPRESSION_H

class Expression {
public:
    static Expression *parse(const char *);
    double calculate();
    struct Node {
        union e {
            int num;
            char opr;
        } data;
        Node *left, *right;
        bool isNum;
    };
    Node *root;
    int size;

private:
    static const char *opr;
    static Node *initNode(Node::e data, bool isNum);
    static bool isOpr(char);
    static bool isDigit(char);
    static int readNum(const char *&ptr);
    static bool validate(const char *expression);
    static int judge_priority(char, char);
    static double calculate(Node *);
};

#endif //ALGORITHM_EXPRESSION_H
//void preOrder(void (*visit)(Node *)) {
//    preOrder(root, visit);
//}
//
//static void preOrder(Expression::Node *node, void (*visit)(Expression::Node *)) {
//    if (node) {
//        visit(node);
//        preOrder(node->left, visit);
//        preOrder(node->right, visit);
//    }
//}
//
//void inOrder(void (*visit)(Node *)) {
//    inOrder(root, visit);
//}
//
//static void inOrder(Expression::Node *node, void (*visit)(Expression::Node *)) {
//    if (node) {
//        inOrder(node->left, visit);
//        visit(node);
//        inOrder(node->right, visit);
//    }
//}