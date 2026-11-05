/* 0x003c17b0 - beNDMWMdlEnemy_GetReadyMetaObject. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct SFUN_003c17b0 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_003c17b0 *DAT_0058b508[4];
extern "C" void FUN_003c1860(void);
extern "C" SFUN_003c17b0 *beNDMWMdlEnemy_GetReadyMetaObject(void) {
    if (DAT_0058b508[0] == 0 || !DAT_0058b508[0]->ok()) FUN_003c1860();
    return DAT_0058b508[0];
}
