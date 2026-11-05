/* 0x00356b10 - FUN_00356b10. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct SFUN_00356b10 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_00356b10 *DAT_00588e58[4];
extern "C" void FUN_00356b60(void);
extern "C" SFUN_00356b10 *FUN_00356b10(void) {
    if (DAT_00588e58[0] == 0 || !DAT_00588e58[0]->ok()) FUN_00356b60();
    return DAT_00588e58[0];
}
