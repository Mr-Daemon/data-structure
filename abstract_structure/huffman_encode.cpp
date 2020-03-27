//
// Created by cyb12 on 2020/2/15.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include "huffman_encode.h"

void Encoder::initWList(const char *text) {
    for (int i = 0; i < 26; ++i) {
        wList[i] = 0;
    }
    while (*text) {
        if (*text <= 'z' && *text >= 'a') {
            wList[*text - 'a']++;
        } else if (*text <= 'Z' && *text >= 'A') {
            wList[*text - 'A']++;
        }
        ++text;
    }
}

void Encoder::initNode(Encoder::Node *node, char c, int weight) {
    *node = {c, weight, -1, -1, -1};
}

void Encoder::initTree() {
    leaf_num = 0;
    for (int i = 0; i < 26; ++i) {
        if (wList[i]) {
            leaf_num++;
            std::cout << (char) (i + 'a') << ":" << wList[i] << " ";
        }
    }
    std::cout << "\n";
    array = (Node *) malloc((2 * leaf_num - 1) * sizeof(Node));
    int currentIndex = 0;
    for (int j = 0; j < 26; ++j) {
        if (wList[j]) {
            initNode(array + currentIndex, 'a' + j, wList[j]);
            currentIndex++;
        }
    }
}

void Encoder::sortArray() {
    sort(array, 0, leaf_num);
}

void Encoder::sort(Node *list, int start, int end) {
    if (start + 1 < end) {
        sort(list, start, (start + end) / 2);
        sort(list, (start + end) / 2, end);
        auto temp = (Node *) malloc((end - start) * sizeof(Node));
        std::merge(list + start, list + (start + end) / 2, list + (start + end) / 2, list + end, temp, cmp);
        memcpy(list + start, temp, (end - start) * sizeof(Node));
        free(temp);
    }
}

bool Encoder::cmp(Node i, Node j) {
    return i.weight < j.weight;
}

void Encoder::createTree() {
    initTree();
    sortArray();
    int len = leaf_num;
    int current = leaf_num;
    array[0].parent = len;
    array[1].parent = len;
    array[len++] = {'\0', array[0].weight + array[1].weight, 0, 1, -1};
    int a = -1, b = -1;
    int i = 2;
    while (len < 2 * leaf_num - 1) {
        if (a == -1 || b == -1) {
            if (i >= leaf_num || (current < len && array[i].weight >= array[current].weight)) {
                if (a == -1)a = current;
                else b = current;
                current++;
            } else {
                if (a == -1)a = i;
                else b = i;
                i++;
            }
        } else {
            array[a].parent = len;
            array[b].parent = len;
            array[len++] = {'\0', array[a].weight + array[b].weight, a, b, -1};
            a = -1;
            b = -1;
        }
    }
}

void Encoder::getCode(int nodeIndex, char *buffer, int index, char dest[][26]) {
    auto node = array[nodeIndex];
    if (node.alphabet) {
        buffer[index] = '\0';
        printf("%c:%s  ", node.alphabet, buffer);
        strcpy(dest[node.alphabet - 'a'], buffer);
    } else {
        index++;
        buffer[index - 1] = '0';
        getCode(node.left, buffer, index, dest);
        buffer[index - 1] = '1';
        getCode(node.right, buffer, index, dest);
    }
}

void Encoder::initInfo() {
    info = EncodeInfo();
    char buffer[leaf_num];
    getCode(2 * leaf_num - 2, buffer, 0, info.info);
    printf("\n");
}

void Encoder::encode() {
    initInfo();
    int encodeLen = 0;
    for (int i = 0; i < 26; ++i) {
        if (wList[i]) {
            encodeLen += wList[i] * strlen(info.info[i]);
        }
    }
    printf("encoded text len:%d\n", encodeLen);
    encoded = (char *) malloc((encodeLen + 1) * sizeof(char));
    int cur = 0;
    int len = 0;
    for (int j = 0; j < strlen(origin); ++j) {
        char c = origin[j];
        if (c >= 'a' && c <= 'z') {
            len++;
        } else if (c >= 'A' && c <= 'Z') {
            len++;
            c += ('a' - 'A');
        } else {
            continue;
        }
//        printf("index: %d, len: %d\n", cur, strlen(info.info[c - 'a']));
        strcpy(encoded + cur, info.info[c - 'a']);
        cur += strlen(info.info[c - 'a']);
    }
    printf("origin text len:%d\n", len);
//    if (strlen(encoded) == encodeLen) {
//        printf("valid encoded text");
//    }
}

Encoder::~Encoder() {
    free(array);
    free(origin);
    free(encoded);
}

Encoder *Encoder::encode(const char *text) {
    auto encoder = (Encoder *) malloc(sizeof(Encoder));
    encoder->origin = (char *) malloc(strlen(text) * sizeof(char));
    strcpy(encoder->origin, text);
    encoder->initWList(text);
    encoder->createTree();
    encoder->encode();
//    for (int i = 0; i < 2 * encoder->leaf_num - 1; ++i) {
//        std::cout << i << "-th "
//                  << "char:" << encoder->array[i].alphabet << " "
//                  << "weight:" << encoder->array[i].weight << " "
//                  << "parent:" << encoder->array[i].parent << " "
//                  << "left:" << encoder->array[i].left << " "
//                  << "right:" << encoder->array[i].right << " "
//                  << "\n";
//    }
    printf("encoded text: %s", encoder->encoded);
    return encoder;
}

Encoder *Encoder::decode(char *text, EncodeInfo *info) {
    return nullptr;
}


//int main(int argc, char const *argv[]) {
//    const char *test = "The 2-D arrays which are declared by the keyword int and able to store integer values are called two dimensional integer arrays. The process of assigning values during declaration is called initialization. TheseArrays can be initialized by putting the curly braces around each row separating by a comma also each element of a matrix should be separated by a comma.";
//    printf("input text: %s\n", test);
//    auto encoder = Encoder::encode(test);
//    return 0;
//}