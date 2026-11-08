int strchr();

int FUN_002e3220(int arg0) {
    if (arg0 == 0) {
        return 0;
    }
    if ((strchr(arg0, 0x2F) == 0) && (strchr(arg0, 0x5C) == 0)) {
        return 0;
    }
    return 1;
}
