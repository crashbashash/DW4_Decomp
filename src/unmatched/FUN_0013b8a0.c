/* 0x0013b8a0 — FUN_0013b8a0. Banked by tools/retype_struct_member.py (shape: width):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
int igAttr_GetMetaObject();
int FUN_002fe290();
extern short GPR_00554b04;

void FUN_0013b8a0(void *arg0) {
    short temp_a0;

    if ((FUN_002fe290(arg0, igAttr_GetMetaObject()) != 0) && (*(unsigned char *)((char *)(arg0) + 26) == 0)) {
        temp_a0 = GPR_00554b04;
        GPR_00554b04 = temp_a0 + 1;
        *(int *)((char *)(arg0) + 8) = (int)((int) temp_a0);
    }
}
