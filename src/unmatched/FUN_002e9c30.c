/* 0x002e9c30 — FUN_002e9c30. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002d8f20();
extern int DAT_004fb410[4];
void FUN_002e9c30(int *arg0, void *arg1) {
    if (*(unsigned char *)((char *)(arg1) + 56) == 0) {
        FUN_002d8f20(arg1);
    }
    *arg0 = DAT_004fb410[0];
}
