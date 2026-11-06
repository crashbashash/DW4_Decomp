int FUN_002a0bb8();
int FUN_002a0dd8();
int FUN_002ad1d0();

int FUN_002ad160(void *arg0, int *arg1) {
    *arg1 = 0;
    if (FUN_002a0dd8() != 0) {
        return FUN_002a0bb8(0, 0xFF000155);
    }
    FUN_002ad1d0(*(int *)((char *)(arg0) + 13864), arg1);
    return 0;
}
