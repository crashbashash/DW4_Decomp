/* 0x00174850 - FUN_00174850. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
int FUN_001e74b0();
int FUN_001e7500();
extern int DAT_005609a0[4];
extern unsigned char GPR_00554b64;
struct S174 { char pad[1373]; unsigned char f; };
void FUN_00174850(struct S174 *arg0, int arg1) {
    int temp_v1;
    if (GPR_00554b64 != 0) {
        arg1 = 0;
    }
    temp_v1 = arg1 & 0xFF;
    if (arg0->f == temp_v1) {
        DAT_005609a0[0] += 1;
    }
    arg0->f = arg1;
    if (temp_v1 == 1) {
        FUN_001e7500(0x13, arg1);
        return;
    }
    FUN_001e74b0(0x13, arg1);
}
