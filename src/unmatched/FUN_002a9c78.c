/* 0x002a9c78 — FUN_002a9c78. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0028b180();
extern int DAT_00585630[4];
void FUN_002a9c78(void *arg0) {
    FUN_0028b180(*(int *)((char *)(arg0) + 8120) + 0x10D0, &DAT_00585630[0], 0x48);
}
