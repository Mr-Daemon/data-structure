//
// Created by cyb12 on 2020-01-23.
//
#include <cstring>
#include <cstdio>

int count = 0;

int len(const char *c_str) {
    int length = 0;
    while (*(c_str + length)) {
        length++;
    }
    return length;
}

//start search at pos
//time complexity -> O(len(str)*len(pattern))
//The Naive pattern searching algorithm
void naive_match(char *str, char *pattern, int *result, int &len) {
    //m,n is length of c_str; i,j is the index of the char to be compared
    int m = strlen(str), n = strlen(pattern), i = 0, j = 0;
    len = 0;
    while (i <= m) {
        if (j == n) {
            result[len++] = i - j;
            j = 0;
        }
        if (str[i] == pattern[j]) {
            i++;
            j++;
        } else {
            i += 1 - j;
            j = 0;
        }
    }
}

//preprocess the pattern
//pre[i] is the num of prefix of pattern[0:i], i is not the index of mismatch
//i = mismatch index - 1
//the pros of this is, if you need to match duplicate pattern,
//after you get a match index, you can let pattern index = pre[length - 1]
void preprocess(const char *const pattern, int *const pre) {
    pre[0] = 0;
    int length = 0;//length of previous longest prefix
    int i = 1;
    while (i < strlen(pattern)) {
        if (pattern[length] == pattern[i]) {
            length++;
            pre[i++] = length;
        } else if (length == 0)
            pre[i++] = 0;
            //tricky, use the previous result
        else length = pre[length - 1];
    }
}


//match fun after optimising
//Knuth Morris Pratt (KMP) algorithm
//only execute i++ to change the value of i!
void kmp_match(const char *const str, const char *const pattern, int *result, int &length) {
    //m,n is length of c_str; i,j is the index of the char to be compared
    int m = strlen(str), n = strlen(pattern), i = 0, j = 0;
    length = 0;
    int pre[n];
    preprocess(pattern, pre);
    for (int k = 0; k < n; ++k)
        printf("%d ", pre[k]);
    printf("\n");
    while (i <= m) {
        if (j == n) {
            result[length++] = i - j;
            //j=0 when match without duplicating
            //j=pre[j-1] when match with duplicating
            j = 0;
        }
        if (str[i] == pattern[j]) {
            i++;
            j++;
        } else if (!j)
            i++;
        else
            //j-1!!! j is the mismatch index, but pre[i] is the length
            //of prefix of pattern[0:i], we need change j to the length of prefix
            //of pattern[0:j-1]
            j = pre[j - 1];
    }

}

int main(int argc, char const *argv[]) {
    char str[100] = "AAAABAAAAABBBAAAAB";
    char pattern[100] = "AAAA";
    int result[100];
    int length;
    kmp_match(str, pattern, result, length);
    for (int i = 0; i < length; ++i) {
        printf("%d ", result[i]);
    }
    return 0;
}