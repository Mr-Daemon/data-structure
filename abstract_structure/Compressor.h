//
// Created by cyb12 on 2020/4/20.
//

#ifndef DATA_STRUCTURE_COMPRESSOR_H
#define DATA_STRUCTURE_COMPRESSOR_H

#include <iostream>
#include <fstream>
#include <cstring>

class Compressor {
    static const char *const POSTFIX;
    std::ifstream in;
    int inputBits;
    std::ofstream out;
    int outputBits;
    bool bitsLeft;
    u_int8_t bit;
    //key: code+char(20 bits); code:12bits
    u_int32_t dict[4096];
    char cDict[4096];
    //@param mode: true for compress
    Compressor(const char *path, bool mode);
    void insert(u_int32_t key, u_int16_t value);
    u_int16_t find(u_int32_t key);
    static const int DIVISOR;
    void setFiles(const char *path, bool mode);
    void output(u_int16_t pCode);
    void compress();
    void decode(u_int16_t code);
    bool getCode(u_int16_t &code);
    void uncompress();
public:
    static void compress(const char *path);
    static void uncompress(const char *path);
};


#endif //DATA_STRUCTURE_COMPRESSOR_H
