/* Matches only with the alternate (combat) compiler build. */
extern int DAT_004c22f0[4];
int FUN_002d9710(void *arg0, int arg1) {
    int var_v0;

    var_v0 = *(int *)((char *)((*(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 16) + (arg1 * 4)))) + 8);
    if (var_v0 == 0) {
        var_v0 = DAT_004c22f0[0];
    }
    return var_v0;
}
