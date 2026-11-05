void FUN_00465df0(void *arg0, int arg1, char arg2) {
    if ((*(unsigned char *)((char *)(arg0) + 117) != 0) && ((arg1 == 0xC8) || (arg1 == 0xC9))) {
        *(char *)((char *)(arg0) + 116) = arg2;
    }
    if (arg1 != 0xCA) {
        if (arg1 == 0xCB) {
            goto block_7;
        }
    } else {
block_7:
        *(char *)((char *)(arg0) + 108) = arg2;
        *(int *)((char *)(arg0) + 112) = 0;
    }
}
