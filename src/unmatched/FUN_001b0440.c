int FUN_001b0250();

void FUN_001b0440(int a0, int a1) {
    *(int *)((char *)a1 + 8) = 0;
    FUN_001b0250(a0, a1);
}
