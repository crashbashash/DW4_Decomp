/* 0x0026efb8 — FUN_0026efb8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0026efb8(void *arg0, void *arg1, void *arg2) {
    *(unsigned short *)((char *)(arg1) + 0) = (unsigned short) *(unsigned short *)((char *)(arg0) + 40);
    *(unsigned short *)((char *)(arg2) + 0) = (unsigned short) *(unsigned short *)((char *)(arg0) + 42);
    *(unsigned short *)((char *)(arg1) + 2) = (unsigned short) *(unsigned short *)((char *)(arg0) + 44);
    *(unsigned short *)((char *)(arg2) + 2) = (unsigned short) *(unsigned short *)((char *)(arg0) + 46);
}
