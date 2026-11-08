extern const char _ctype_[];

int _tolower(int c) {
    return ((_ctype_ + 1)[c] & 1) ? c + ('a' - 'A') : c;
}
