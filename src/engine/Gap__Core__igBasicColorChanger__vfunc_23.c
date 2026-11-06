int Gap__Core__igBasicColorChanger__vfunc_23(int arg0, void *arg1) {
    int i;
    if (*(unsigned char *)((char *)(arg1) + 12) == 0) {
        return arg0 + 0x48;
    }
    i = 0;
    if (*(unsigned char *)((char *)(arg1) + 13) != 0) {
        i = i + 1;
    }
    if (*(unsigned char *)((char *)(arg1) + 15) != 0) {
        i = i + 2;
    }
    return arg0 + i * 0x10 + 8;
}
