/* 0x001754b0 - FUN_001754b0. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
int FUN_001e8be0();
extern int DAT_0048a520[4];
extern int DAT_005609e4[4];
struct S1754 { char pad[1428]; int f; char tail[1]; };
int FUN_001754b0(struct S1754 *arg0, int arg1) {
    if (arg0->f == arg1) {
        DAT_005609e4[0] += 1;
    }
    arg0->f = arg1;
    return FUN_001e8be0(DAT_0048a520[arg1], (char *)arg0 + 0x598) != 0;
}
