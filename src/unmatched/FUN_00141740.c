/* 0x00141740 — FUN_00141740. Banked by tools/retype_struct_member.py (shape: width):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
int FUN_0013b810();
int FUN_0013b820();

void FUN_00141740(void *arg0) {
    FUN_0013b820();
    FUN_0013b810(arg0, *(short *)((char *)(arg0) + 16));
}
