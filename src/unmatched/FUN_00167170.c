/* 0x00167170 — FUN_00167170. Banked by tools/retype_struct_member.py (shape: width):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
int Matrix44_Copy();

void FUN_00167170(void *arg0) {
    Matrix44_Copy((char *)arg0 + 0x6C);
    *(char *)((char *)(arg0) + 236) = 1;
}
