/* 0x00245270 — FUN_00245270. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002452d0(int, int, int, int);
int FUN_00245310();

void FUN_00245270(int arg0) {
    FUN_00245310();
    FUN_002452d0(arg0, *(int *)0x56DED8, *(int *)0x4986C8, *(int *)0x4986C0);
    *(int *)0x56DED0 = (int) (*(int *)0x56DED0 + 1);
}
