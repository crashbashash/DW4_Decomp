/* 0x0034d940 - FUN_0034d940. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct SFUN_0034d940 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_0034d940 *DAT_00588688[4];
extern "C" void FUN_0034d9d0(void);
extern "C" SFUN_0034d940 *FUN_0034d940(void) {
    if (DAT_00588688[0] == 0 || !DAT_00588688[0]->ok()) FUN_0034d9d0();
    return DAT_00588688[0];
}
