int strncpy();

void FUN_002d3320(char *arg0, char *arg1) {
    if ((arg1 != 0) && (*arg1 != 0)) {
        strncpy(arg0 + 528, arg1, 0x7F);
        arg0[655] = 0;
        return;
    }
    arg0[528] = 0;
}
