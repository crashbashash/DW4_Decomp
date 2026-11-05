/* 0x00294648 — FUN_00294648. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ad950();
int FUN_00294698();

void FUN_00294648(int *arg0) {
    int temp_s1;

    temp_s1 = *(int *)((char *)(arg0) + 64);
    FUN_002ad950(temp_s1, 0x4B, &FUN_00294698);
    FUN_002ad950(temp_s1, 0x4C, arg0);
}
