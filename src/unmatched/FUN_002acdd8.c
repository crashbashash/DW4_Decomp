int FUN_002a0bb8();
int FUN_002a0dd8();
int FUN_002ace48();

int FUN_002acdd8(void *arg0, int *arg1) {
    *arg1 = 0;
    if (FUN_002a0dd8() != 0) {
        return FUN_002a0bb8(0, 0xFF000154);
    }
    FUN_002ace48(*(int *)((char *)(arg0) + 13864), arg1);
    return 0;
}
