/* 0x0029a428 — FUN_0029a428. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0029a450();

void FUN_0029a428(void *arg0) {
    if (*(int *)((char *)(arg0) + 100) == 1) {
        FUN_0029a450();
    }
}
