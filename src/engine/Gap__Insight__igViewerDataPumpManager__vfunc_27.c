int FUN_001e68a0();
int FUN_00236be0();
int igObject_IsKindOf();
extern int DAT_00562c10[4];
int Gap__Insight__igViewerDataPumpManager__vfunc_27(void *arg0, int arg1) {
    if (igObject_IsKindOf(arg1, DAT_00562c10[0]) != 0) {
        FUN_001e68a0(*(int *)((char *)(arg0) + 16), arg1);
        FUN_00236be0(*(int *)((char *)(arg0) + 12), arg0);
        return 1;
    }
    return 0;
}
