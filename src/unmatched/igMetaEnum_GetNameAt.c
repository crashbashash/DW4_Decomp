/* 0x002fbbd0 — igMetaEnum_GetNameAt. Banked by tools/retype_struct_member.py (shape: leadcall0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
int StringList_CopyRetained();

void igMetaEnum_GetNameAt(int *arg0, void *arg1, int arg2) {
    void *temp_a1;

    temp_a1 = (void *)(*(int *)((char *)(arg1) + 12));
    if ((temp_a1 != 0) && (arg2 >= 0) && (arg2 < *(int *)((char *)(temp_a1) + 8))) {
        StringList_CopyRetained(arg0, temp_a1);
        return;
    }
    *arg0 = 0;
}
