int FUN_001904f0();

void FUN_001e6b00(void *arg0, int arg1) {
    int p;
    p = *(int *)((char *)(arg0) + 16) + ((*(int *)((char *)(arg0) + 8) - 1) << 6);
    FUN_001904f0(p, p, arg1);
}
