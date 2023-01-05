#include <iostream>


class CipherStateMachine {
    bool bufX[19] = {};
    bool bufY[22] = {};
    bool bufZ[23] = {};

    static void _shiftRight(bool* buf, int len) {
        for (int i = len - 2; i >= 0; i--) {
            buf[i + 1] = buf[i];
        }
    }
    static bool _majority(bool x, bool y, bool z) {
        int c0 = 0;
        int c1 = 0;
        c0 += !x + !y + !z;
        c1 += x + y + z;
        return c0 < c1;
    }

public:
    explicit CipherStateMachine(const bool *keyBuf) {
        for (int i = 0; i < 19; i++) {
            this->bufX[i] = (bool) keyBuf[i];
        }
        for (int i = 19; i < 41; i++) {
            this->bufY[i - 19] = (bool) keyBuf[i];
        }
        for (int i = 41; i < 64; i++) {
            this->bufZ[i - 41] = (bool) keyBuf[i];
        }
    }
    explicit CipherStateMachine(const int *keyBuf) {
        for (int i = 0; i < 19; i++) {
            this->bufX[i] = (bool) keyBuf[i];
        }
        for (int i = 19; i < 41; i++) {
            this->bufY[i - 19] = (bool) keyBuf[i];
        }
        for (int i = 41; i < 64; i++) {
            this->bufZ[i - 41] = (bool) keyBuf[i];
        }
    }
    void display() const {
        for (auto dat : bufX) {
            std::cout << (int)dat;
        }
        std::cout << " ";
        for (auto dat : bufY) {
            std::cout << (int)dat;
        }
        std::cout << " ";
        for (auto dat : bufZ) {
            std::cout << (int)dat;
        }
        std::cout << std::endl;
    }
    bool next() {
        bool result = bufX[18] ^ bufY[21] ^ bufZ[22];
        bool majority = _majority(bufX[8], bufY[10], bufZ[10]);
        if (bufX[8] == majority) {
            _shiftRight(bufX, 19);
            bufX[0] = bufX[13] ^ bufX[16] ^ bufX[17] ^ bufX[18];
        }
        if (bufY[10] == majority) {
            _shiftRight(bufY, 22);
            bufY[0] = bufY[20] ^ bufY[21];
        }
        if (bufZ[10] == majority) {
            _shiftRight(bufZ, 23);
            bufY[0] = bufY[7] ^ bufY[20] ^ bufY[21] ^ bufY[22];
        }
        return result;
    }
};

int main() {
    int key[64] = {
            1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
            1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
            1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,
    };

    auto stateMachine = new CipherStateMachine(key);
    stateMachine->display();
    for (int i = 0; i < 60; i++) {
        std::cout << stateMachine->next();
    }
    std::cout << std::endl;
}