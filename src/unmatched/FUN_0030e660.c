int FUN_00129ef8();
extern int DAT_004fb440[4];
int FUN_0030e660(void *arg0, char *arg1, int arg2) {
    int sp2C;
    int sp28;

    sp2C = 0;
    sp28 = 0;
    FUN_00129ef8(arg2, &DAT_004fb440[0], &sp28, &sp2C);
    *arg1 = (char) sp28;
    return sp2C;
}
