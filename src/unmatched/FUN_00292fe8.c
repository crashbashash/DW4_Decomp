int mwsfd_Error();
extern int DAT_004f2f58[4];
extern int DAT_004f2f88[4];
int FUN_00292fe8(void *arg0) {
    int var_a0;

    var_a0 = 1;
    if (*(int *)((char *)(arg0) + 0) == 2) {
        mwsfd_Error(&DAT_004f2f58[0]);
        var_a0 = 0;
    }
    if ((unsigned int) *(int *)((char *)(arg0) + 36) >= 3U) {
        mwsfd_Error(&DAT_004f2f88[0]);
        var_a0 = 0;
    }
    return var_a0;
}
