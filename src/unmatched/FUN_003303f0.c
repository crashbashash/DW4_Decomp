/* 0x003303f0 — FUN_003303f0. Banked by tools/retype_struct_member.py (shape: leadcall0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
int FUN_00330440();

void FUN_003303f0(void *arg0) {
    if (*(unsigned char *)((char *)(arg0) + 57) != 0) {
        FUN_00330440(arg0, 0);
    }
    *(char *)((char *)(arg0) + 58) = 1;
}
