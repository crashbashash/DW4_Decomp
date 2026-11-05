/* 0x003ba2a0 - FUN_003ba2a0. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct SFUN_003ba2a0 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_003ba2a0 *DAT_0058af18[4];
extern "C" void FUN_003ba6a0(void);
extern "C" SFUN_003ba2a0 *FUN_003ba2a0(void) {
    if (DAT_0058af18[0] == 0 || !DAT_0058af18[0]->ok()) FUN_003ba6a0();
    return DAT_0058af18[0];
}
