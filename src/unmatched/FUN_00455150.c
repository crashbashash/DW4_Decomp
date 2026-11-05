/* 0x00455150 — FUN_00455150. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_004552e0(int, void *, void *);

void FUN_00455150(void *arg0, void *arg1) {
    int temp_a0;

    if ((*(int *)((char *)arg1 + 0) == 0) || (*(int *)((char *)arg0 + 16) == *(int *)((char *)arg1 + 8))) {
        temp_a0 = *(int *)((char *)arg0 + 12);
        if (temp_a0 != 0) {
            FUN_004552e0(temp_a0, arg0, arg0);
        }
    }
}
