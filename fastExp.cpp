//
// Created by khanh on 1/13/2023.
//
#include <iostream>
#include <cstring>

template<typename T>
class BitArray {
public:
    int length = sizeof(T) * 8;
private:
    bool *data = (bool *) calloc(length, sizeof(bool));
public:
    explicit BitArray(T input) {
        memset(this->data, 0, length * sizeof(bool));
        int curIndex = this->length - 1;
        while (input != 0 && curIndex >= 0) {
            this->data[curIndex] = input % 2;
            input >>= 1;
            curIndex--;
        }
    }

    bool get(int index) {
        return this->data[index];
    }

    void destroy() {
        free(data);
        free(this);
    }
};


int fastExp(int base, int exp, int mod) {
    if (mod <= 0) {
        std::throw_with_nested("Invalid modulus!");
    }
    if (base < 0 || exp < 0) {
        std::throw_with_nested("Invalid base or exponents!");
    }
    if (exp == 0) {
        if (base > 0) {
            return 1;
        } else {
            std::throw_with_nested("0 ** 0 is invalid.");
        }
    }
    auto expBitArray = new BitArray<int>(exp);
    int current = 1;
    for (int i = 0; i < expBitArray->length; i++) {
        current *= current;
        current %= mod;
        if (expBitArray->get(i) == 1) {
            current *= base;
            current %= mod;
        }
    }
    expBitArray->destroy();
    return current;
}

int main() {
    std::cout << fastExp(5, 9, 2000) << std::endl;
}