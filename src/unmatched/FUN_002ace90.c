/* 0x002ace90 — FUN_002ace90. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002aced8();
int FUN_002ad738();

void FUN_002ace90(void *arg0) {
    if (*(int *)((char *)(arg0) + 13864) == 0) {
        return;
    }
    FUN_002aced8();
    FUN_002ad738(arg0);
}
