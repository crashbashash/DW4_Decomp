/* 0x0032fe90 — FUN_0032fe90. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_004fb410[];
extern char DAT_004fb418[];
int FUN_0010bd90(int);

void FUN_0032fe90(int *arg0, void *arg1) {
    int *var_v1;

    if (FUN_0010bd90(*(int *)((char *)arg1 + 60)) < 0) {
        var_v1 = (int *)DAT_004fb418;
    } else {
        var_v1 = (int *)DAT_004fb410;
    }
    *arg0 = *var_v1;
}
