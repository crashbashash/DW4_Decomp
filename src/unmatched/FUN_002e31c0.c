int strchr();

int FUN_002e31c0(char *arg0) {
    char c;

    if (arg0 == 0) {
        return 0;
    }
    c = *arg0;
    if (c == 0x2F || c == 0x5C) {
        return 1;
    }
    return strchr(arg0, 0x3A) != 0;
}
