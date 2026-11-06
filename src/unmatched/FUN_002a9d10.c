int FUN_002a8f90();
int FUN_002a96e0();

int FUN_002a9d10(void *arg0, int arg1) {
    if (FUN_002a96e0() == 0) {
        return arg1;
    }
    return FUN_002a8f90(*(int *)((char *)(arg0) + 8120) + 0x1118, arg1);
}
