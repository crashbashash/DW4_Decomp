extern int DAT_004c22f0[4];
extern int DAT_004fb160[4];
int FUN_00307f80(void *arg0, int arg1) {
    int var_v0;

    if (arg1 < 0xB) {
        return DAT_004fb160[arg1];
    }
    var_v0 = *(int *)((char *)(*(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 16)) + 16) + (arg1 * 4))) - 44)) + 8);
    if (var_v0 == 0) return DAT_004c22f0[0]; return var_v0;
}
