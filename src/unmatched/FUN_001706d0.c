/* 0x001706d0 - FUN_001706d0. typed unsigned char member, int parameter; alternate compiler -O3 Verified byte-identical by tools/verify.py. */
typedef struct S0 { char pad1340[1340]; unsigned char f1340; } S0;
int FUN_001e74b0();
int FUN_001e7500();
extern long long DAT_00560848[4];
extern unsigned char GPR_00554b44;

void FUN_001706d0(S0 *arg0, int arg1) {
    if (arg0->f1340 == (arg1 & 0xFF)) {
        DAT_00560848[0] += 1;
    }
    if (GPR_00554b44 != 0) {
        arg1 = 0;
    }
    arg0->f1340 = arg1;
    if (arg0->f1340 == 1) {
        FUN_001e74b0(8, arg1);
        return;
    }
    FUN_001e7500(8, arg1);
}
