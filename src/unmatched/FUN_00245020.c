/* 0x00245020 — FUN_00245020. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00245080(int, int, int, int);
int FUN_002450c0();

void FUN_00245020(int arg0) {
    FUN_002450c0();
    FUN_00245080(arg0, *(int *)0x56DEC0, *(int *)0x4986B8, *(int *)0x4986B0);
    *(int *)0x56DEB8 = (int) (*(int *)0x56DEB8 + 1);
}
