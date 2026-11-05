/* 0x00295e40 — FUN_00295e40. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0029cf78();

void FUN_00295e40(void *arg0) {
    FUN_0029cf78(*(int *)((char *)(arg0) + 64));
}
