/* 0x00341e10 - FUN_00341e10. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct SFUN_00341e10 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_00341e10 *DAT_00587c98[4];
extern "C" void FUN_00341f40(void);
extern "C" SFUN_00341e10 *FUN_00341e10(void) {
    if (DAT_00587c98[0] == 0 || !DAT_00587c98[0]->ok()) FUN_00341f40();
    return DAT_00587c98[0];
}
