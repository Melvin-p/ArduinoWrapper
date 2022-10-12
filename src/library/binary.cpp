#include "binary.hpp"

unsigned int makeWord(unsigned int w) {
    return w;
}

unsigned int makeWord(unsigned char h, unsigned char l) {
    return (h << 8) | l;
}