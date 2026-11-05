/* 0x002ea280 — FUN_002ea280. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ea280(void *arg0) {
    return (*(int *)((char *)(arg0) + 52) * 4) & 0xFFFF;
}
