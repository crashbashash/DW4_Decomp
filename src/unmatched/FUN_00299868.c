/* 0x00299868 — FUN_00299868. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void *FUN_00299f58();
int (**FUN_00299f68())();

void FUN_00299868(void) {
    int (**temp_v0)();
    int (*temp_v1)();
    void *temp_s0;

    temp_s0 = (void *)(FUN_00299f58());
    temp_v0 = (int (*)())(FUN_00299f68());
    if ((temp_v0 != 0) && (*(int *)((char *)(temp_s0) + 4) == 0)) {
        temp_v1 = (int (*)())(*temp_v0);
        if (temp_v1 != 0) {
            temp_v1();
        }
        *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) + 1));
    }
}
