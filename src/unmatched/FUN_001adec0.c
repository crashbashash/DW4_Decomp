/* 0x001adec0 — FUN_001adec0. m2c draft, hybrid; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
int FUN_001ab8b0();
int FUN_001ad990();

int FUN_001adec0(void *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    int sp8C;
    int var_v0;

    FUN_001ab8b0(arg1, *(int *)((char *)arg0 + 12), &sp8C);
    var_v0 = 0;
    if (sp8C != 0) {
        var_v0 = FUN_001ad990(arg0, arg1, arg2, arg3, arg4, arg5, arg6, sp8C);
    }
    return var_v0;
}
