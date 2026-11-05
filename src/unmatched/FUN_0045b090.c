/* 0x0045b090 — FUN_0045b090. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igObject_InitHeader();
extern int DAT_0052d060[4];
void *FUN_0045b090(void *arg0) {
    igObject_InitHeader();
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_0052d060[0]);
    *(int *)((char *)(arg0) + 8) = 0;
    return arg0;
}
