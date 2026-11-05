/* 0x00295d30 — FUN_00295d30. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00295c00();
int FUN_002968c0();
int FUN_002971b0();
int FUN_0029a320();
extern int DAT_004f3950[4];
extern int DAT_004f3988[4];
void FUN_00295d30(void **arg0, int arg1, int arg2, int arg3) {
    if (FUN_002968c0() == 0) {
        FUN_0029a320(&DAT_004f3950[0]);
        return;
    }
    if (arg1 == 0) {
        FUN_0029a320(&DAT_004f3988[0]);
        return;
    }
    ((int (*)())*(int *)((char *)((*arg0)) + 60))(arg0, FUN_002971b0(arg0));
    FUN_00295c00(arg0, arg1, arg2, arg3);
}
