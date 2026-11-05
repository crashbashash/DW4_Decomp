/* 0x0029a570 — FUN_0029a570. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0029a598();
int FUN_0029a690();

void FUN_0029a570(void *arg0) {
    if (*(int *)((char *)(arg0) + 660) == 1) {
        FUN_0029a598();
        return;
    }
    FUN_0029a690();
}
