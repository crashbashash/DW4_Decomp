/* 0x003ca1e0 - beNDMWGameRamInfoRam_ResolveMetaObject. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct SFUN_003ca1e0 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_003ca1e0 *DAT_0058c100[4];
extern "C" void FUN_003ca2d0(void);
extern "C" SFUN_003ca1e0 *beNDMWGameRamInfoRam_ResolveMetaObject(void) {
    if (DAT_0058c100[0] == 0 || !DAT_0058c100[0]->ok()) FUN_003ca2d0();
    return DAT_0058c100[0];
}
