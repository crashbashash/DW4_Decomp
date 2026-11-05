int FUN_00190330(int, int);
int igObject_IsKindOf(void *, int);
extern int DAT_00561010[4];
int FUN_0022d520(void *arg0, int arg1, void *arg2, int arg3) {
    void *r0;
    void *r2;
    if (arg0 != 0 && igObject_IsKindOf(arg0, DAT_00561010[0]) != 0) {
        r0 = arg0;
    } else {
        r0 = 0;
    }
    if (arg2 != 0 && igObject_IsKindOf(arg2, DAT_00561010[0]) != 0) {
        r2 = arg2;
    } else {
        r2 = 0;
    }
    if (r0 != 0 && r2 != 0) {
        FUN_00190330(arg3 + *(int *)((char *)r2 + 8), arg1 + *(int *)((char *)r0 + 8));
        return 1;
    }
    return 0;
}
