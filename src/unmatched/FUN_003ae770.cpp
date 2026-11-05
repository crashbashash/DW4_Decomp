/* 0x003ae770 — FUN_003ae770. Banked by tools/retype_struct_member.py (shape: struct2):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
typedef struct S0 { char pad36[36]; int f24; } S0;
typedef struct S1 { char pad48[48]; int f30; } S1;
extern "C" {
int FUN_003ad950(int, int);
int FUN_003ada60(int);
int FUN_003add40(int, int);
void FUN_003ae770(S0 *arg0, S1 *arg1);
}

void FUN_003ae770(S0 *arg0, S1 *arg1) {
    FUN_003ad950(arg0->f24, arg1->f30);
    FUN_003ada60(arg0->f24);
    FUN_003add40(arg0->f24, arg1->f30);
}
