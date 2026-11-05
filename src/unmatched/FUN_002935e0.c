/* 0x002935e0 — FUN_002935e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void *FUN_00294a30();

void FUN_002935e0(int arg0) {
    void *temp_v0;

    temp_v0 = (void *)(FUN_00294a30());
    ((int (*)())*(int *)((char *)(temp_v0) + 40))(*(int *)((char *)(temp_v0) + 48), arg0);
}
