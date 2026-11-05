void *FUN_00307c10(int, int, int, int);
int FUN_0030b770();

int FUN_00307750(int arg0, int arg1, int arg2, int arg3) {
    void *temp_v0;

    temp_v0 = (void *)(FUN_00307c10(arg0, arg1, arg2, 1));
    if (temp_v0 == 0) {
        return 0;
    }
    FUN_0030b770(*(int *)((char *)(temp_v0) + 12), arg3, 0);
    return 1;
}
