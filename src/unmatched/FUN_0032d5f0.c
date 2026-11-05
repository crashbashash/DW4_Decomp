/* 0x0032d5f0 — FUN_0032d5f0. Banked by tools/retype_struct_member.py (shape: struct0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
typedef struct S0 { char pad8[8]; int f8; int fC; int f10; } S0;
int DeleteSema();
int FUN_00300f50();
int WaitSema();

void FUN_0032d5f0(S0 *arg0) {
    if (arg0->fC != 0) {
        WaitSema(arg0->f10);
        FUN_00300f50(arg0, arg0->fC);
    }
    FUN_00300f50(arg0, arg0->f8);
    DeleteSema(arg0->f10);
}
