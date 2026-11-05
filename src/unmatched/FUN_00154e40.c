/* 0x00154e40 — FUN_00154e40. Banked by tools/retype_struct_member.py (shape: leadcall0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
typedef struct S0 { char pad12[12]; int fC; int f10; int f14; int f18; } S0;
int FUN_00300ea0();

void FUN_00154e40(S0 *arg0, int arg1) {
    if (arg1 != arg0->fC) {
        arg0->f14 = FUN_00300ea0(arg0, arg0->f14, arg1 * arg0->f10, 0x80);
        arg0->fC = arg1;
        arg0->f18 = (int)((int) (arg1 * arg0->f10));
    }
}
