/* 0x0025c578 — FUN_0025c578. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0025c260();
int FUN_0025c3f8();

void FUN_0025c578(void *arg0) {
    if (*(short *)((char *)(arg0) + 156) == 1) {
        FUN_0025c3f8();
        return;
    }
    FUN_0025c260();
}
