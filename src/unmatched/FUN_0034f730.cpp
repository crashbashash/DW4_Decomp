/* 0x0034f730 - FUN_0034f730. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct SFUN_0034f730 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_0034f730 *DAT_005887c8[4];
extern "C" void FUN_0034f7c0(void);
extern "C" SFUN_0034f730 *FUN_0034f730(void) {
    if (DAT_005887c8[0] == 0 || !DAT_005887c8[0]->ok()) FUN_0034f7c0();
    return DAT_005887c8[0];
}
