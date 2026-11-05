int FUN_0032ac70();

int FUN_0032ad50(int arg0, unsigned int arg1, int arg2, int arg3, int arg4) {
    int n = 0;
    for (; arg1 < 0x4000U; arg1++) {
        if (arg2-- == 0) return n;
        if (arg3 != (arg4 & FUN_0032ac70(arg0, arg1))) return n;
        n++;
    }
    return n;
}
