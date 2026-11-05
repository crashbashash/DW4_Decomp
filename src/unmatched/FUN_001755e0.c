/* 0x001755e0 - FUN_001755e0. typed unsigned char member, int parameter Verified byte-identical by tools/verify.py. */
typedef struct S0 { char pad1449[1449]; unsigned char f1449; } S0;
int FUN_001e8b80();
extern int DAT_005609ec[4];
void FUN_001755e0(S0 *arg0, int arg1) {
    if (arg0->f1449 == (arg1 & 0xFF)) {
        DAT_005609ec[0] += 1;
    }
    arg0->f1449 = arg1;
    if (arg1 != 0) {
        FUN_001e8b80(1);
        return;
    }
    FUN_001e8b80(0);
}
