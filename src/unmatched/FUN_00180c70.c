/* 0x00180c70 — FUN_00180c70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00560588[4];
int FUN_00180c70(void) {
    return DAT_00560588[0];
}
