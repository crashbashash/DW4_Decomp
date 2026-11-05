/* 0x0026c568 — FUN_0026c568. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002607e8();
extern int DAT_004ee790[4];
short FUN_0026c568(int arg0, int arg1) {
    if (arg0 == 0) {
        FUN_002607e8(&DAT_004ee790[0]);
        return 0;
    }
    return *(int *)((char *)(((arg1 * 2) + arg0)) + 66);
}
