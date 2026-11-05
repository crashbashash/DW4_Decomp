/* 0x00267738 — FUN_00267738. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00267540();
int FUN_00267580();
extern int DAT_004a5d58[4];
extern int DAT_004ee3e8[4];
int FUN_00267738(int arg0, int arg1, int arg2) {
    if (DAT_004a5d58[0] == 0) {
        FUN_00267540();
    }
    FUN_00267580(&DAT_004ee3e8[0], 6, arg0, arg1, arg2);
    return 0;
}
