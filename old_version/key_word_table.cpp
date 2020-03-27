//
// Created by cyb12 on 2020-01-24.
//

#include <c++/cstdio>
#include <c++/cstdlib>
#include <c++/cstring>

const char *commonWord[] = {"of", "to", "and", "in", "the", "The", "by"};

int cmp(char *word) {// 1 represent word is not in commonWord
    int length = sizeof(commonWord) / sizeof(commonWord[0]);
    for (int i = 0; i < length; ++i)
        if (!strcmp(word, commonWord[i]))
            return 0;
    return 1;
}


class Entry {
    char *keyWord;
    typedef struct node {
        int num;
        node *next;
    } node, *nodePtr;
    nodePtr head;
public:
    Entry(char *keyWord, int serialNum) {
        //keyword must point to str that terminated with '\0'
        this->keyWord = (char *) malloc((strlen(keyWord) + 1) * sizeof(char));
        strcpy(this->keyWord, keyWord);
        //init the serialNum list
        head = (nodePtr) malloc(sizeof(node));
        auto newNode = (nodePtr) malloc(sizeof(node));
        head->next = newNode;
        newNode->num = serialNum;
        newNode->next = nullptr;
    }

    void addSerialNum(int serialNum) {
        nodePtr ptr = head->next;
        int num = ptr->num;
        while (ptr->next) {
            num = ptr->num;
            ptr = ptr->next;
        }
        if (serialNum == num)
            return;
        //generate a new node add to the end of serialNum list
        auto newNode = (nodePtr) malloc(sizeof(node));
        newNode->num = serialNum;
        newNode->next = ptr->next;
        ptr->next = newNode;
    }

    const char *getKeyWord() {
        return keyWord;
    }

    const node *getHeadNode() {
        return head;
    }
};

class Table {
    static const int INIT_LENGTH = 20;
    static const int INCREMENT = 20;
    Entry *table;
    int length;

    int search(char *search) {
        for (int i = 0; i < length; ++i)
            if (!strcmp(search, table[i].getKeyWord()))
                return i;
        return -1;
    }

public:
    Table() : length(0) {
        table = (Entry *) malloc(sizeof(Entry) * INIT_LENGTH);
    }

    void insert(char *keyWord, int serialNum) {
        int i = search(keyWord);
        if (i != -1)
            table[i].addSerialNum(serialNum);
        else
            table[length++] = *(new Entry(keyWord, serialNum));
    }

    int getLength() {
        return length;
    }

    void getEntry(int i) {
        auto entry = table[i];
        printf("%s: ", entry.getKeyWord());
        auto node = entry.getHeadNode();
        while (node->next) {
            node = node->next;
            printf("%d ", node->num);
        }
        printf("\n");
    }
};

int main(int argc, char const *argv[]) {
    char str[1000];
    //file content require format like "[\d]{3}" 3-digit serial number and book name in every line
    FILE *f = fopen(R"(C:\playground\algorithm\data_structure\test.txt)", "r");
    Table table;
    while (fscanf(f, "%[^\n]\n", str) != EOF) {
        char buffer[50];
        int length = 0;
        int multi = 100;
        int serialNum = 0;//assume serialNum has three digits
        for (int i = 0; i <= strlen(str); ++i) {//<= ensure we can access '\0'
            if (str[i] >= '0' && str[i] <= '9') {
                serialNum += (str[i] - '0') * multi;
                multi /= 10;
            } else if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
                buffer[length++] = str[i];
            } else if (length) {//extract a word
                buffer[length] = '\0';//manually add terminated char at end
                if (cmp(buffer)) {
//                    printf("insert keyword: %s serialNum: %d\n", buffer, serialNum);
                    table.insert(buffer, serialNum);
                }
                length = 0;
            }
        }
    }
    for (int j = 0; j < table.getLength(); ++j) {
        table.getEntry(j);
    }
    return 0;
}
