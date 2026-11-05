/* 0x0022a740 — FUN_0022a740. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0022cb80();
int List_InsertWords();

int FUN_0022a740(int arg0, void **arg1) {
    int temp_v0;
    void *temp_v1;

    temp_v1 = *arg1;
    if (temp_v1 != 0) {
        *(int *)((char *)(temp_v1) - 4) = (int) (*(int *)((char *)(temp_v1) - 4) + 1);
    }
    temp_v0 = FUN_0022cb80(arg0, arg1);
    List_InsertWords(arg0, temp_v0, 1, arg1);
    return temp_v0;
}
