int FUN_002f2cd0(int arg0, int arg1) {
    int i;
    if (arg1 != 0) {
        for (i = 0; i < 0x2E; i++) {
            if (arg1 == *(int *)((char *)((arg0 + (i * 0x90))) + 20)) {
                return i;
            }
        }
    }
    return -1;
}
