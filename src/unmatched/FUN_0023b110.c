/* 0x0023b110 — FUN_0023b110. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0018d630();

void FUN_0023b110(void *arg0, void *arg1) {
    if (*(int *)((char *)(arg1) + 96) == 0) {
        FUN_0018d630(*(int *)((char *)(arg0) + 8), (char *)arg1 + 0x20);
    }
}
