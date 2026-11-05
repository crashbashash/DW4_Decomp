int FUN_0023c9a0();
int *FUN_0023c920(int *arg0, int *arg1, unsigned int arg2) {
    int sp[3];
    FUN_0023c9a0(sp, arg2 & 0x1F, (arg2 >> 5) & 3, (arg2 >> 7) & 7, arg1[(arg2 >> 10) & 0x3FFFFF]);
    arg0[0] = sp[0];
    arg0[1] = sp[1];
    arg0[2] = sp[2];
    return arg0;
}
