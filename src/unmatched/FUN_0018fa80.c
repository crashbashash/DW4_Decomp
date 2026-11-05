/* 0x0018fa80 - FUN_0018fa80. Near-miss sweep fix, verified byte-identical to retail by tools/verify.py. */
extern void * DAT_00561118[4];
int FUN_0018fa80(void *arg0, void *arg1) {
    int var_v0;
    unsigned int temp_v1;
    unsigned int temp_a0;

    temp_a0 = *(int *)((char *)(arg0) + 8);
    temp_v1 = *(int *)((char *)(arg1) + 8);
    if (temp_a0 < temp_v1) {
        var_v0 = (temp_v1 * (temp_v1 + 2)) - temp_a0;
    } else {
        var_v0 = temp_v1 + (temp_a0 * temp_a0);
    }
    return *(int *)(*(int *)((char *)(DAT_00561118[0]) + 16) + (var_v0 * 4));
}
