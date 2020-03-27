//
// Created by cyb12 on 2020-02-03.
//

#include <c++/cstdlib>
#include <c++/cstring>
#include <c++/iostream>
#include "expression.h"

const char *Expression::opr = "+-*/";

Expression::Node *Expression::initNode(Node::e data, bool isNum) {
    auto node = (Expression::Node *) malloc(sizeof(Expression::Node));
    *node = {data, nullptr, nullptr, isNum};
    return node;
}

bool Expression::isOpr(char c) {
    for (unsigned i = 0; i < strlen(opr); ++i) {
        if (opr[i] == c)
            return true;
    }
    return false;
}

bool Expression::isDigit(char c) {
    return c >= '0' && c <= '9';
}

int Expression::readNum(const char *&ptr) {
    char buffer[10];
    int cur = 0;
    while (isDigit(*ptr)) {
        buffer[cur++] = *ptr - '0';
        ++ptr;
    }
    int multi = 1, result = 0;
    while (cur) {
        result += buffer[--cur] * multi;
        multi *= 10;
    }
    return result;
}

bool Expression::validate(const char *expression) {
    bool hold_opr = false, opr_preserved = false;
    int cur = 0;
    for (unsigned i = 0; i < strlen(expression); ++i) {
        if (isDigit(expression[i])) {
            hold_opr = true;
            opr_preserved = false;
        } else if (isOpr(expression[i]) && hold_opr) {
            hold_opr = false;
            opr_preserved = true;
        } else if (expression[i] == '(' && !hold_opr) {
            hold_opr = false;
            opr_preserved = false;
            cur++;
        } else if (expression[i] == ')' && !opr_preserved) {
            hold_opr = true;
            cur--;
            if (cur < 0)return false;
        } else return false;
    }
    return cur == 0;
}

int Expression::judge_priority(char c1, char c2) {
    if (c1 == '-')c1 = '+';
    if (c1 == '/')c1 = '*';
    if (c2 == '-')c2 = '+';
    if (c2 == '/')c2 = '*';
    if (!(c1 + c2)) return 0;
    else if (c1 == '(' && c2 == ')') return 0;
    else if (c1 == '(' && c2 == '(') return 1;
    else if (c1 == c2)return -1;
    else if (c1 == '+' && c2 == '*') return 1;
    else if (c1 == '*' && c2 == '+') return -1;
    else if (c1 == '(' || c2 == '(')return 1;
    else if (c2 == ')')return -1;
    else if (!c1)return 1;
    else if (!c2) return -1;
    else return 0;
}

Expression *Expression::parse(const char *expression) {
    if (validate(expression)) {
        const char *ptr = expression;
        int size = 0;
        char opr_stk[strlen(expression)];
        Node *opd_stk[strlen(expression)];
        int opr_cur = 0, opd_cur = 0;
        opr_stk[opr_cur++] = '\0';
        while (*ptr) {
            if (isDigit(*ptr)) {
                opd_stk[opd_cur++] = initNode({readNum(ptr)}, true);
                size++;
            } else {
                int num = judge_priority(opr_stk[opr_cur - 1], *ptr);
                if (!num) {
//                    std::cout << opr_stk[opr_cur - 1] << "=" << *ptr << "\n";
                    opr_cur--;
                    ptr++;
                } else if (num > 0) {
//                    std::cout << opr_stk[opr_cur - 1] << "<" << *ptr << "\n";
                    opr_stk[opr_cur++] = *ptr;
                    ptr++;
                } else {
//                    std::cout << opr_stk[opr_cur - 1] << ">" << *ptr << "\n";
                    auto node = initNode({opr_stk[--opr_cur]}, false);
                    size++;
                    node->right = opd_stk[--opd_cur];
                    node->left = opd_stk[--opd_cur];
                    opd_stk[opd_cur++] = node;
                }
            }
        }
        auto result = (Expression *) malloc(sizeof(Expression));
        result->root = initNode({opr_stk[--opr_cur]}, false);
        size++;
        result->root->right = opd_stk[--opd_cur];
        result->root->left = opd_stk[--opd_cur];
        result->size = size;
        return result;
    } else
        return nullptr;
}

double Expression::calculate(Expression::Node *node) {
    if (node->isNum) {
        return node->data.num;
    } else {
        switch (node->data.opr) {
            case '+':
                return calculate(node->left) + calculate(node->right);
            case '-':
                return calculate(node->left) - calculate(node->right);
            case '*':
                return calculate(node->left) * calculate(node->right);
            case '/':
                return calculate(node->left) / calculate(node->right);
        }
    }
    return 0;
}

double Expression::calculate() {
    return calculate(root);
}


void print(Expression::Node *node) {
    if (node->isNum)
        std::cout << node->data.num;
    else
        std::cout << node->data.opr;
}


int main(int argc, char const *argv[]) {
    const char *expression = "((1+4)*5+3)*3";
    auto expression_binary_tree = Expression::parse(expression);
    std::cout << expression_binary_tree->calculate();
    return 0;
}