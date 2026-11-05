/* 0x00192f00 — FUN_00192f00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_00192f00(void *arg0, void *arg1, void *arg2, float fparg0) {
    float temp_f1;
    float temp_f1_2;
    float temp_f1_3;

    temp_f1 = *(float *)((char *)(arg1) + 0);
    *(float *)((char *)(arg0) + 0) = (float) (temp_f1 + (fparg0 * (*(float *)((char *)(arg2) + 0) - temp_f1)));
    temp_f1_2 = *(float *)((char *)(arg1) + 4);
    *(float *)((char *)(arg0) + 4) = (float) (temp_f1_2 + (fparg0 * (*(float *)((char *)(arg2) + 4) - temp_f1_2)));
    temp_f1_3 = *(float *)((char *)(arg1) + 8);
    *(float *)((char *)(arg0) + 8) = (float) (temp_f1_3 + (fparg0 * (*(float *)((char *)(arg2) + 8) - temp_f1_3)));
}
