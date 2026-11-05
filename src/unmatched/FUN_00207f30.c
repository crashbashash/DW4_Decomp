/* 0x00207f30 — FUN_00207f30. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001f76c0();
extern void * DAT_0056ad80[4];
extern int DAT_0056bfb8[4];
extern int DAT_0056bfd8[4];
int FUN_00207f30(int arg0) {
    int temp_a1;

    temp_a1 = DAT_0056bfb8[0] + 1;
    DAT_0056bfb8[0] = temp_a1;
    *(int *)((char *)DAT_0056ad80[0] + 424) = temp_a1;
    *(int *)((char *)DAT_0056ad80[0] + 428) = -1;
    DAT_0056bfd8[0] += 1;
    if (arg0 != 0) {
        FUN_001f76c0(0x35, temp_a1);
    }
    return DAT_0056bfb8[0];
}
