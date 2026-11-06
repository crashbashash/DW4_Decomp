int FUN_00303cd0();
int FUN_00303dc0();
int FUN_00304030();

void FUN_001cb2d0(int dummy0, int arg1, int arg2, void *arg3) {
    int temp_v0;

    temp_v0 = FUN_00303dc0(arg1, arg2);
    if (temp_v0 != -1) {
        FUN_00304030(arg1, temp_v0);
    }
    FUN_00303cd0(arg1, arg2, *(int *)((char *)(arg3) + 28));
}
