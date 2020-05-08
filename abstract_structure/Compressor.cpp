//
// Created by cyb12 on 2020/4/20.
//

#include "Compressor.h"

const char *const Compressor::POSTFIX = ".lzw";
const int Compressor::DIVISOR = 4096;

void Compressor::insert(u_int32_t key, u_int16_t value) {
    u_int16_t pos = key % DIVISOR;
    while (dict[pos] && (dict[pos] >> 12u) != key) {
        pos = (pos + 1) % DIVISOR;
    }
    dict[pos] = (key << 12u) + value;
}

u_int16_t Compressor::find(u_int32_t key) {
    u_int16_t pos = key % DIVISOR;
    while (dict[pos]) {
        if ((dict[pos] >> 12u) == key) {
            return dict[pos] << 20u >> 20u;
        }
        pos = (pos + 1) % DIVISOR;
    }
    return 0;
}

void Compressor::setFiles(const char *path, bool mode) {
    int len = strlen(path);
    in.open(path, std::ios::binary);
    std::string line;
    char outName[len + strlen(POSTFIX)];
    if (mode) {
        strcpy(outName, path);
        strcat(outName, POSTFIX);
    } else {
        strncpy(outName, path, len - strlen(POSTFIX));
    }
    out.open(outName, std::ios::binary);
    if (out.is_open()) {
        std::cout << "outfile open\n";
    } else {
        std::cout << "failed\n";
    }
}

void Compressor::output(u_int16_t pCode) {
    if (bitsLeft) {
        int a = (bit << 4u) + (pCode >> 8u);
        out.put(a);
        out.put(pCode & 255u);
        outputBits += 16;
    } else {
        out.put(pCode >> 4u);
        bit = pCode & 31u;
        outputBits += 8;
    }
    bitsLeft = !bitsLeft;
}

void Compressor::compress() {
    for (u_int16_t i = 0; i < 256; ++i) {
        insert(i, i + 1);
    }
    u_int16_t codeUsed = 256;
    int c = in.get();
    if (c != EOF) {
        u_int16_t pCode = c;
        inputBits += 8;
        while ((c = in.get()) != EOF) {
            inputBits += 8;
            u_int32_t key = (pCode << 8u) + c;
            if (find(key)) {
                pCode = find(key);
            } else {
                output(pCode);
                if (codeUsed < 4096) {
                    std::cout << "insert:" << pCode << "," << (char) c << ":" << codeUsed << "\n";
                    insert(key, codeUsed++);
                }
                pCode = c;
            }
        }
        if (bitsLeft) {
            out.put(bit << 4u);
            outputBits += 4;
        }
    }
    std::cout << "input:" << inputBits << "\noutput:" << outputBits;
}

Compressor::Compressor(const char *path, bool mode) {
    bitsLeft = false;
    inputBits = outputBits = bit = 0;
    memset(dict, 0, 4096 * sizeof(u_int32_t));
    setFiles(path, mode);
    if (mode) {
        compress();
    } else {
        uncompress();
    }
    for (int i = 256; i < 4096; ++i) {
        if (dict[i]) {
            std::cout << i << "-th " << (dict[i] >> 20u) << "," << (dict[i] >> 12u & 255u) << ":"
                      << (dict[i] << 20u >> 20u) << "\n";
        }
    }
}

void Compressor::compress(const char *path) {
    Compressor(path, true);
}

void Compressor::decode(u_int16_t code) {

}

bool Compressor::getCode(u_int16_t &code) {
    char a, b;
    if ((a = in.get()) == EOF)return false;
    if (bitsLeft) {
        code = (bit << 8u) + a;
    } else {
        b = in.get();
        code = (a << 4u) + (b >> 4u);
        bit = b & 31;
    }
    bitsLeft = !bitsLeft;
    return true;
}

void Compressor::uncompress() {
    u_int16_t codeUsed = 256;
    int pCode, cCode;
    if()
}

void Compressor::uncompress(const char *path) {
    Compressor(path, false);
}




