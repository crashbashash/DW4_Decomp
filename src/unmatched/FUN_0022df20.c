/* 0x0022df20 - 188 bytes. Two dynamic casts (null-or-wrong-class gives 0) then a copy between the two objects' fields. */
int igObject_IsKindOf();
extern int DAT_00586598[4];
int FUN_0022df20(void *arg0, int arg1, void *arg2, int arg3) {
    int r;
    void *a;
    void *b;
    if (arg0 != 0 && igObject_IsKindOf(arg0, DAT_00586598[0]) != 0) {
        a = arg0;
    } else {
        a = 0;
    }
    if (arg2 != 0 && igObject_IsKindOf(arg2, DAT_00586598[0]) != 0) {
        b = arg2;
    } else {
        b = 0;
    }
    if (a != 0 && b != 0) {
        *(int *)(arg3 + *(int *)((char *)(b) + 8)) = *(int *)(arg1 + *(int *)((char *)(a) + 8));
        return 1;
    }
    return 0;
}
