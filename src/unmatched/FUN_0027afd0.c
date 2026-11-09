extern int DAT_004b1dc8;
extern int DAT_004b1dc0;
int FUN_0027afd0(void *arg0, int arg1) {
    if (DAT_004b1dc8 == 1 && DAT_004b1dc0 <= 0) {
        return 0;
    }
    return ((int *)((char *)arg0 + 64))[arg1];
}
