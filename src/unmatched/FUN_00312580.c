/* 0x00312580 — FUN_00312580. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00310c00(int);
int igArenaMemoryPool_CheckHeap(int *);

void FUN_00312580(int *arg0, int arg1) {
    int sp3C;

    igArenaMemoryPool_CheckHeap(&sp3C);
    FUN_00310c00(arg1);
    *arg0 = sp3C;
}
