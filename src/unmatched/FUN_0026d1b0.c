int FUN_002607e8();
int FUN_002670c0();
extern int DAT_004eebf0[4];
int FUN_0026d1b0(void *arg0) {
    if (arg0 == 0) {
        FUN_002607e8(&DAT_004eebf0[0]);
        return -1;
    }
    return FUN_002670c0(*(int *)((char *)(arg0) + 4));
}
