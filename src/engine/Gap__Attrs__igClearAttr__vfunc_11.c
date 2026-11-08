int FUN_001931b0();
float dptofp();
int Gap__Core__igObject__vfunc_09();

void Gap__Attrs__igClearAttr__vfunc_11(void *arg0) {
    Gap__Core__igObject__vfunc_09();
    *(int *)((char *)(arg0) + 60) = FUN_001931b0((char *)arg0 + 0x10, 1);
    *(float *)((char *)(arg0) + 64) = dptofp(*(long long *)((char *)(arg0) + 48));
}
