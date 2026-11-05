/* 0x00308770 — FUN_00308770. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004c22d8[4];
extern int * DAT_004c22e0[4];
int FUN_00308400();
extern char GPR_00554c30;

void FUN_00308770(void) {
    DAT_004c22e0[0] = (int *)(&FUN_00308400);
    GPR_00554c30 = 0;
    DAT_004c22d8[0] = 5;
}
