int _ipuFlushBits();
int FUN_00106c88();
int FUN_001073e0();

int FUN_00106e78(void *arg0) {
    *(int *)((char *)(arg0) + 460) = FUN_00106c88(arg0, 5);
    if (FUN_00106c88(arg0, 1) != 0) {
        FUN_00106c88(arg0, 1);
        _ipuFlushBits(arg0, 7);
        FUN_001073e0(arg0);
    }
    return 0;
}
