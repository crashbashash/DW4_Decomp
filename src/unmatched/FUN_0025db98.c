/* 0x0025db98 — FUN_0025db98. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0026efb8();
int FUN_0026eff0();

void FUN_0025db98(void *arg0) {
    FUN_0026efb8(*(int *)((char *)(arg0) + 8), (char *)arg0 + 0xAC, (char *)arg0 + 0xB0);
    FUN_0026eff0(*(int *)((char *)(arg0) + 8), (char *)arg0 + 0xA6, (char *)arg0 + 0xA8, (char *)arg0 + 0xAA);
}
