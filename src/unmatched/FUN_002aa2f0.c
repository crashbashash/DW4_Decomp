int FUN_002a0bb8();
int FUN_002a0dd8();

int FUN_002aa2f0(void *arg0) {
    if (FUN_002a0dd8() != 0) {
        FUN_002a0bb8(0, 0xFF000141);
        return 0;
    }
    return *(int *)((char *)(arg0) + 80);
}
