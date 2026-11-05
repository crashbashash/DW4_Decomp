/* 0x0018fad0 - FUN_0018fad0. Matches only with the alternate (combat) compiler build; see docs/engine/unit-compilers.md. */
extern void * DAT_00561120[4];
int FUN_0018fad0(void *arg0, void *arg1) {
    int var_v0;
    unsigned int temp_a0;
    unsigned int temp_v1;

    temp_a0 = *(int *)((char *)(arg0) + 8);
    temp_v1 = *(int *)((char *)(arg1) + 8);
    if (temp_a0 < temp_v1) {
        var_v0 = (temp_v1 * (temp_v1 + 2)) - temp_a0;
    } else {
        var_v0 = temp_v1 + (temp_a0 * temp_a0);
    }
    return *(int *)(*(int *)((char *)(DAT_00561120[0]) + 16) + (var_v0 * 4));
}
