/* 0x0045dc20 - igLogoRenderer_GetMetaObject. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct SigLogoRenderer_GetMetaObject { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SigLogoRenderer_GetMetaObject *DAT_0058cdf0[4];
extern "C" void FUN_0045dd20(void);
extern "C" SigLogoRenderer_GetMetaObject *igLogoRenderer_GetMetaObject(void) {
    if (DAT_0058cdf0[0] == 0 || !DAT_0058cdf0[0]->ok()) FUN_0045dd20();
    return DAT_0058cdf0[0];
}
