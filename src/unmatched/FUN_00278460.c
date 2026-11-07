int FUN_00277de8();
extern int DAT_004f0e30[4];
char FUN_00278460(void *arg0) {
    if (arg0 == 0) {
        FUN_00277de8(arg0, &DAT_004f0e30[0]);
        return 0;
    }
    return *(int *)((char *)(arg0) + 1);
}
