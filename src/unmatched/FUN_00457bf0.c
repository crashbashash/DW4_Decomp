/* 0x00457bf0 — FUN_00457bf0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00457ab0(int, void *, void *);

void FUN_00457bf0(void *arg0, void *arg1) {
    if ((*(int *)((char *)arg1 + 8) == *(int *)0x58C290) || (*(int *)((char *)arg1 + 0) == 0)) {
        FUN_00457ab0(*(int *)((char *)arg0 + 12), arg0, arg0);
    }
}
