/* 0x003687a0 - FUN_003687a0. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct SFUN_003687a0 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_003687a0 *DAT_00589b80[4];
extern "C" void FUN_003688d0(void);
extern "C" SFUN_003687a0 *FUN_003687a0(void) {
    if (DAT_00589b80[0] == 0 || !DAT_00589b80[0]->ok()) FUN_003688d0();
    return DAT_00589b80[0];
}
