/* 0x002f8af0 — FUN_002f8af0. Banked by tools/retype_struct_member.py (shape: struct0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
typedef struct S0 { char pad20[20]; int f14; } S0;
int ObjectList_RemoveFirstRetained();

void FUN_002f8af0(S0 *arg0, int arg1) {
    int sp1C;

    ObjectList_RemoveFirstRetained(&sp1C, arg0->f14, arg1, 0);
}
