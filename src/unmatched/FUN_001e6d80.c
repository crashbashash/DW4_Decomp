int FUN_00129ef8();
int FUN_0018be80();

int FUN_001e6d80(int arg0, int *arg1, int arg2) {
    if (arg2 != 0) {
        return FUN_00129ef8(arg0, arg2, arg1, arg1 + 1, arg1 + 2, arg1 + 3) == 4;
    }
    return FUN_0018be80(arg0, arg1, 4, 4, 1) != 0;
}
