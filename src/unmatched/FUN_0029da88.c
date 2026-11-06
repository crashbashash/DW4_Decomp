void FUN_0029da88(void *arg0) {
    int var_v0;
    void *var_a0;

    var_a0 = (void *)(arg0);
    var_v0 = 2;
    do {
        var_v0 -= 1;
        *(int *)((char *)(var_a0) + 0) = 0;
        *(int *)((char *)(var_a0) + 4) = 0;
        *(int *)((char *)(var_a0) + 8) = 0;
        *(int *)((char *)(var_a0) + 12) = 0;
        var_a0 = (void *)((char *)var_a0 + (0x10));
    } while (var_v0 >= 0);
}
