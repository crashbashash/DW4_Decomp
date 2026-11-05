/* 0x003b58b0 - FUN_003b58b0. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct SFUN_003b58b0 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_003b58b0 *DAT_0058abf8[4];
extern "C" void FUN_003b5900(void);
extern "C" SFUN_003b58b0 *FUN_003b58b0(void) {
    if (DAT_0058abf8[0] == 0 || !DAT_0058abf8[0]->ok()) FUN_003b5900();
    return DAT_0058abf8[0];
}
