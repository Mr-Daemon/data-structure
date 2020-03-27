//
// Created by cyb12 on 2020/2/15.
//

#ifndef DATA_STRUCTURE_HUFFMAN_ENCODE_H
#define DATA_STRUCTURE_HUFFMAN_ENCODE_H

class EncodeInfo {
public:
    char info[26][26];

};


class Encoder {
    struct Node {
        char alphabet;
        int weight;
        int left, right, parent;
    };
    Node *array;
    int wList[26];
    int leaf_num;
    EncodeInfo info;
    char *origin;
    char *encoded;
    void initWList(const char *text);
    static void initNode(Node *node, char c, int weight);
    void initTree();
    void sortArray();
    static void sort(Node *list, int start, int end);
    static bool cmp(Node i, Node j);
    void createTree();
    void getCode(int nodeIndex, char *buffer, int index, char dest[][26]);
    void initInfo();
    void encode();
    ~Encoder();
public:
    static Encoder *encode(const char *text);
    static Encoder *decode(char *text, EncodeInfo *info);
};


#endif //DATA_STRUCTURE_HUFFMAN_ENCODE_H
