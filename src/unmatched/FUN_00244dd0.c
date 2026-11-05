/* 0x00244dd0 — FUN_00244dd0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00244e30(int, int, int, int);
int FUN_00244e70();

void FUN_00244dd0(int arg0) {
    FUN_00244e70();
    FUN_00244e30(arg0, *(int *)0x56DEA8, *(int *)0x4986A8, *(int *)0x4986A0);
    *(int *)0x56DEA0 = (int) (*(int *)0x56DEA0 + 1);
}
