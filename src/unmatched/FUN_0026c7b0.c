/* 0x0026c7b0 — FUN_0026c7b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002607e8();
extern int DAT_004a8e58[4];
extern int DAT_004ee880[4];
void FUN_0026c7b0(void *arg0, int arg1) {
    if (arg0 == 0) {
        FUN_002607e8(&DAT_004ee880[0]);
        return;
    }
    *(int *)((char *)(arg0) + 56) = arg1;
    DAT_004a8e58[0] = arg1;
}
