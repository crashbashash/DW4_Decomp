/* 0x002dbc10 — FUN_002dbc10. Banked by tools/retype_struct_member.py (shape: struct0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
typedef struct S0 { char pad52[52]; int f34; } S0;
int FUN_002db480();
int FUN_002db540();

int FUN_002dbc10(S0 *arg0, int arg1) {
    char *temp_a0;

    FUN_002db480();
    temp_a0 = (char *)(arg0->f34);
    if (*temp_a0 != 0x28) {
        return 0;
    }
    arg0->f34 = (int)((char *) (temp_a0 + 1));
    if (FUN_002db540(arg0, arg1) == 0) {
        return 0;
    }
    FUN_002db480(arg0);
    arg0->f34 = (int)((char *) (arg0->f34 + 1));
    return 1;
}
