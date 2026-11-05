int igObject_IsKindOf(void *, int);
extern int DAT_00585760[4];
int FUN_0022d820(void *arg0, int arg1, void *arg2, int arg3) {
    void *r0;
    void *r2;
    if (arg0 != 0 && igObject_IsKindOf(arg0, DAT_00585760[0]) != 0) {
        r0 = arg0;
    } else {
        r0 = 0;
    }
    if (arg2 != 0 && igObject_IsKindOf(arg2, DAT_00585760[0]) != 0) {
        r2 = arg2;
    } else {
        r2 = 0;
    }
    if (r0 != 0 && r2 != 0) {
        *(unsigned char *)(arg3 + *(int *)((char *)r2 + 8)) = *(unsigned char *)(arg1 + *(int *)((char *)r0 + 8));
        return 1;
    }
    return 0;
}
