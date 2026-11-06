int igStrCmp();

int FUN_002f2b30(int arg0, char *arg1) {
    int i;

    if (arg1 != 0 && *arg1 != 0) {
        for (i = 0; i < 0x2E; i++) {
            if (igStrCmp(arg0 + (i * 0x90) + 0x18, arg1) == 0) {
                return i;
            }
        }
    }
    return -1;
}
