/* 0x0025deb0 — FUN_0025deb0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0026f130();

void FUN_0025deb0(void *arg0) {
    if (*(int *)((char *)(arg0) + 4) == 3) {
        FUN_0026f130(*(int *)((char *)(arg0) + 8));
        *(int *)((char *)(arg0) + 140) = 0;
        *(int *)((char *)(arg0) + 4) = 0;
    }
}
