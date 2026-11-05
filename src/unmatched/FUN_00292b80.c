/* 0x00292b80 — FUN_00292b80. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0027bd48();

void FUN_00292b80(void *arg0) {
    FUN_0027bd48(*(int *)((char *)(arg0) + 472), *(int *)((char *)(arg0) + 476), *(int *)((char *)(arg0) + 480));
}
