int sscanf();
extern int DAT_004c22f0[4];
extern int DAT_004f9738[4];
int FUN_0030b630(void *arg0, int arg1) {
    int var_a0;

    var_a0 = *(int *)((char *)(arg0) + 8);
    if (var_a0 == 0) {
        var_a0 = DAT_004c22f0[0];
    }
    return sscanf(var_a0, &DAT_004f9738[0], arg1) == 1;
}
