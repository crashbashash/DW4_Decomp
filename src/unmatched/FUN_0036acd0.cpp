/* 0x0036acd0 - FUN_0036acd0. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct SFUN_0036acd0 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_0036acd0 *DAT_00589de8[4];
extern "C" void FUN_0036ad20(void);
extern "C" SFUN_0036acd0 *FUN_0036acd0(void) {
    if (DAT_00589de8[0] == 0 || !DAT_00589de8[0]->ok()) FUN_0036ad20();
    return DAT_00589de8[0];
}
