/* 0x0034b120 - FUN_0034b120. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct SFUN_0034b120 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_0034b120 *DAT_005883c8[4];
extern "C" void FUN_0034b260(void);
extern "C" SFUN_0034b120 *FUN_0034b120(void) {
    if (DAT_005883c8[0] == 0 || !DAT_005883c8[0]->ok()) FUN_0034b260();
    return DAT_005883c8[0];
}
