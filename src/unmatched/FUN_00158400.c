/* 0x00158400 — FUN_00158400. Banked by tools/retype_struct_member.py (shape: struct0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
typedef struct S0 { char pad48[48]; int f30; int f34; char pad60[4]; unsigned char f3C; } S0;
int FUN_00158480();
int Memory_FreeBuffer();

void FUN_00158400(S0 *arg0, int arg1, int arg2) {
    int temp_a0;

    temp_a0 = arg0->f34;
    if ((temp_a0 != 0) && (arg0->f3C != 0)) {
        Memory_FreeBuffer(temp_a0);
    }
    arg0->f34 = arg1;
    arg0->f3C = 0U;
    FUN_00158480(arg0);
    arg0->f30 = arg2;
}
