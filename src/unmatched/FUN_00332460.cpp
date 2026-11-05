extern "C" {
/* 0x00332460 — FUN_00332460. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0026c6c8(int);

int FUN_00332460(void *arg0) {
    int temp_a0;

    temp_a0 = *(int *)((char *)arg0 + 44);
    if (temp_a0 == 0) {
        return 0;
    }
    return FUN_0026c6c8(temp_a0);
}
}
