int FUN_00129ef8();
extern int DAT_004c22f0[4];
extern int DAT_004f9730[4];
int FUN_0030b5f0(void *arg0, int arg1) {
    int var_a0;

    var_a0 = *(int *)((char *)(arg0) + 8);
    if (var_a0 == 0) {
        var_a0 = DAT_004c22f0[0];
    }
    return FUN_00129ef8(var_a0, &DAT_004f9730[0], arg1) == 1;
}
