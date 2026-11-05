int igObject_IsKindOf();
extern int DAT_00585948[4];
int FUN_0022d9e0(int *arg0, int arg1, int *arg2, int arg3) {
    int r; int *s1;
    s1 = arg2;
    if (arg0 != 0 && igObject_IsKindOf(arg0, DAT_00585948[0]) != 0) { asm { nop } } else { arg0 = 0; }
    if (s1 != 0 && igObject_IsKindOf(s1, DAT_00585948[0]) != 0) { asm { nop } } else { s1 = 0; }
    r = 0;
    if (arg0 != 0 && s1 != 0) {
        r = 1;
        *(short *)(arg3 + s1[2]) = *(short *)(arg1 + arg0[2]);
    }
    return r;
}
