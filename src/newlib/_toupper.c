extern const char _ctype_[];

int _toupper(int c) {
    return ((_ctype_ + 1)[c] & 2) ? c - ('a' - 'A') : c;
}
