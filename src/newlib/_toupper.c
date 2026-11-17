#include <ctype.h>

int _toupper(int c) {
    return ((_ctype_ + 1)[c] & 2) ? c - ('a' - 'A') : c;
}
