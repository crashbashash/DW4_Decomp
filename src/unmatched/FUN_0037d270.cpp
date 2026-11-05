/* 0x0037d270 — FUN_0037d270. Banked by tools/retype_struct_member.py (shape: leadfn1):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
extern "C" {
int FUN_00332d20(int);
int FUN_00333230(int);
void FUN_0037d270(int dummy0, int arg1, int arg2);
}

void FUN_0037d270(int dummy0, int arg1, int arg2) {
    FUN_00332d20(arg1);
    FUN_00333230(arg2);
}
