int FUN_002777f8();
extern int DAT_004f0b08[4];
int FUN_002773d0(void *arg0) {
    if (arg0 == 0) {
        FUN_002777f8(&DAT_004f0b08[0]);
        return -1;
    }
    return *(int *)((char *)(arg0) + 36);
}
