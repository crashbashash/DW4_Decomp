/* 0x002ab810 — FUN_002ab810. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002a0bb8();

int FUN_002ab810(void *arg0) {
    if (*(int *)((char *)(arg0) + 4) == 0) {
        return FUN_002a0bb8(0, 0xFF000204);
    }
    if ((unsigned int) *(int *)((char *)(arg0) + 64) < 0x3718U) {
        return FUN_002a0bb8(0, 0xFF000205);
    }
    return 0;
}
