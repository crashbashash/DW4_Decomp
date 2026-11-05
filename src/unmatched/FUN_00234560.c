long long FUN_001236d0();
int FUN_002345b0();

int FUN_00234560(int arg0, int arg1, int arg2, long long *arg3) {
    int sp2C;

    if (FUN_002345b0(arg0, arg1, arg2, &sp2C) != 0) {
        *arg3 = FUN_001236d0(sp2C);
        return 1;
    }
    return 0;
}
