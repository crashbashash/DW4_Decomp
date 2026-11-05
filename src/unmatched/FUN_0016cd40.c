/* 0x0016cd40 — FUN_0016cd40. Banked by tools/retype_struct_member.py (shape: leadfn1):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
int FUN_002d96f0();
extern int DAT_004df508[4];
extern int DAT_004df510[4];
extern int DAT_004df518[4];
void FUN_0016cd40(int dummy0, int arg1) {
    FUN_002d96f0(arg1, 1, &DAT_004df508[0]);
    FUN_002d96f0(arg1, 2, &DAT_004df510[0]);
    FUN_002d96f0(arg1, 3, &DAT_004df518[0]);
    FUN_002d96f0(arg1, 4, &DAT_004df508[0]);
    FUN_002d96f0(arg1, 5, &DAT_004df510[0]);
}
