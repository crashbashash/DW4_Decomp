/* 0x003bc1f0 - FUN_003bc1f0. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct SFUN_003bc1f0 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_003bc1f0 *DAT_0058b078[4];
extern "C" void FUN_003bc350(void);
extern "C" SFUN_003bc1f0 *FUN_003bc1f0(void) {
    if (DAT_0058b078[0] == 0 || !DAT_0058b078[0]->ok()) FUN_003bc350();
    return DAT_0058b078[0];
}
