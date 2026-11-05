/* 0x002efae0 — FUN_002efae0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void *igProperty_FindByName(int, int, int);

void FUN_002efae0(int arg0, int *arg1, int *arg2) {
    int temp_a0;
    void *temp_v0;

    *arg1 = 0;
    *arg2 = 0;
    temp_a0 = *(int *)0x586F48;
    if (temp_a0 != 0) {
        temp_v0 = igProperty_FindByName(temp_a0, *(int *)0x585BE0, arg0);
        if (temp_v0 != 0) {
            *arg1 = *(int *)((char *)temp_v0 + 12);
            *arg2 = *(int *)((char *)temp_v0 + 16);
        }
    }
}
