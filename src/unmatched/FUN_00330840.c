/* 0x00330840 — FUN_00330840. Banked by tools/retype_struct_member.py (shape: leadcall0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
int FUN_00300f50();

void FUN_00330840(void *arg0) {
    int temp_a1;

    if (*(unsigned char *)((char *)(arg0) + 45) == 0) {
        temp_a1 = *(int *)((char *)(arg0) + 32);
        if (temp_a1 != 0) {
            FUN_00300f50(arg0, temp_a1);
        }
    }
}
