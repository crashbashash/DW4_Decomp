int sscanf();
extern int DAT_004fb440[4];
int Gap__Core__igUnsignedCharMetaField__vfunc_56(void *arg0, char *arg1, int arg2) {
    int sp2C;
    int sp28;

    sp2C = 0;
    sp28 = 0;
    sscanf(arg2, &DAT_004fb440[0], &sp28, &sp2C);
    *arg1 = (char) sp28;
    return sp2C;
}
