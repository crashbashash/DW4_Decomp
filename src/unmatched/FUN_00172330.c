/* 0x00172330 — FUN_00172330. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001f8aa0(int);
int FUN_001f8ae0(int);

void FUN_00172330(void *arg0, void *arg1) {
    FUN_001f8ae0(*(int *)((char *)arg1 + 80));
    FUN_001f8aa0(*(int *)((char *)arg0 + 1344) + 0x58);
}
