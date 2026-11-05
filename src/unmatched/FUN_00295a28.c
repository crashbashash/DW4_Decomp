/* 0x00295a28 — FUN_00295a28. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00295c50();
int FUN_002968c0();
int FUN_002971b0();
int FUN_0029a320();
extern int DAT_004f38c0[4];
void FUN_00295a28(void **arg0, int arg1, int arg2) {
    if (FUN_002968c0() == 0) {
        FUN_0029a320(&DAT_004f38c0[0]);
        return;
    }
    ((int (*)())*(int *)((char *)((*arg0)) + 60))(arg0, FUN_002971b0(arg0));
    FUN_00295c50(arg0, arg1, arg2);
}
