int igObject_IsKindOf();
extern int DAT_00585d80[4];
int FUN_0022dc20(void *arg0, int arg1, void *arg2, int arg3) {
    int var_v0;
    if ((arg0 != 0) && (igObject_IsKindOf(arg0, DAT_00585d80[0]) != 0)) {
        asm { nop }
    } else {
        arg0 = (void *)(0);
    }
    if ((arg2 != 0) && (igObject_IsKindOf(arg2, DAT_00585d80[0]) != 0)) {
        asm { nop }
    } else {
        arg2 = (void *)(0);
    }
    var_v0 = 0;
    if ((arg0 != 0) && (arg2 != 0)) {
        var_v0 = 1;
        *(int *)(arg3 + *(int *)((char *)(arg2) + 8)) = *(int *)(arg1 + *(int *)((char *)(arg0) + 8));
    }
    return var_v0;
}
