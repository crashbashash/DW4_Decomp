int FUN_00306f10();
int FUN_00307660();
void *FUN_00307c10();
extern int DAT_004c22f0[4];
extern int DAT_004f95a0[4];
static inline int pool(void *o) { int a = *(int *)((char *)(*(int *)((char *)(o) + 12)) + 8); if (a == 0) { return DAT_004c22f0[0]; } return a; }
int FUN_00307550(int arg0, int arg1, int arg2, int arg3, int *arg4, int arg5, int arg6) {
    void *temp_v0;
    temp_v0 = (void *)(FUN_00307c10(arg0, arg1, arg2, 0));
    if (temp_v0 != 0) {
        FUN_00306f10(pool(temp_v0), arg4, arg3, &DAT_004f95a0[0]);
    } else {
        *arg4 = arg5;
        if (arg6 != 0) {
            FUN_00307660(arg0, arg1, arg2, arg5);
        }
    }
    return temp_v0 != 0;
}
