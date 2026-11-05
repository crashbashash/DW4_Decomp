int FUN_001b1e50();
int FUN_001c5d10();

int FUN_001dc8e0(void *arg0) {
    int temp_s0;
    int var_a1;
    int a0v;
    void *temp_v0;

    temp_s0 = FUN_001c5d10();
    temp_v0 = (void *)(*(int *)((char *)(arg0) + 28));
    a0v = *(int *)((char *)(arg0) + 32);
    if (temp_v0 != 0) {
        var_a1 = *(int *)((char *)(temp_v0) + 8);
    } else {
        var_a1 = 0;
    }
    FUN_001b1e50(a0v, var_a1);
    return temp_s0;
}
