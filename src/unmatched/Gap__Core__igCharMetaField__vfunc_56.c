int sscanf();
extern int DAT_004f9588[4];
int Gap__Core__igCharMetaField__vfunc_56(void *arg0, char *arg1, int arg2) {
    int sp2C;
    int sp28;
    int t;
    sp2C = 0;
    sp28 = 0;
    sscanf(arg2, DAT_004f9588, &sp28, &sp2C);
    t = sp28;
    *arg1 = t;
    return sp2C;
}
