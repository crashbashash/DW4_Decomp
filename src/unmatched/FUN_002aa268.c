/* 0x002aa268 — FUN_002aa268. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_002aa268(void *arg0) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 8120) + 0x10A8);
    *(int *)((char *)(temp_v1) + 12) = (int)((int) (*(int *)((char *)(temp_v1) + 12) - 1));
}
