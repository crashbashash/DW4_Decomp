int strlen();

char *FUN_001405a0(char *arg0) {
    char *p;
    char c;

    if (arg0 == 0) {
        return 0;
    }
    p = arg0 + strlen(arg0);
    for (; arg0 < p; p--) {
        c = p[-1];
        if (c == 0x5C || c == 0x2F) {
            break;
        }
    }
    return p;
}
