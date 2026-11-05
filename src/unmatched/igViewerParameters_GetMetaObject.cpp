/* 0x0045b470 - igViewerParameters_GetMetaObject. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct SigViewerParameters_GetMetaObject { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SigViewerParameters_GetMetaObject *DAT_0058c9e8[4];
extern "C" void FUN_0045b590(void);
extern "C" SigViewerParameters_GetMetaObject *igViewerParameters_GetMetaObject(void) {
    if (DAT_0058c9e8[0] == 0 || !DAT_0058c9e8[0]->ok()) FUN_0045b590();
    return DAT_0058c9e8[0];
}
