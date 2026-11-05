/* 0x00128f88 — FUN_00128f88. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern void * DAT_004854a0[4];
void FUN_00128f88(long long arg0) {
    *(unsigned long long *)((char *)(DAT_004854a0[0]) + 168) = (unsigned long long) ((unsigned long long) (arg0 << 0x20) >> 0x20);
}
