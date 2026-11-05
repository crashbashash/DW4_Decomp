/* 0x0029af90 — FUN_0029af90. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void *FUN_00294a30();

void FUN_0029af90(void *arg0, int arg1) {
    void *temp_v0;

    temp_v0 = (void *)(FUN_00294a30());
    *(int *)((char *)(arg0) + 96) = arg1;
    *(int *)((char *)(temp_v0) + 36) = arg1;
}
