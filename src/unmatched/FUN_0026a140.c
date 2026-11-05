/* 0x0026a140 — FUN_0026a140. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0026a140(void *arg0, int arg1) {
    int temp_v0;

    temp_v0 = *(int *)((char *)(arg0) + 20);
    *(int *)((char *)(arg0) + 88) = arg1;
    if (temp_v0 < arg1) {
        *(int *)((char *)(arg0) + 88) = temp_v0;
    }
    return *(int *)((char *)(arg0) + 88);
}
