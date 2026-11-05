/* 0x00129670 — FUN_00129670. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00124e10();

int FUN_00129670(void *arg0) {
    if ((*(unsigned short *)((char *)(arg0) + 12) & 9) == 9) {
        return FUN_00124e10();
    }
    return 0;
}
