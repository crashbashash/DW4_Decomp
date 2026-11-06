struct SFUN_003c3d00 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_003c3d00 *DAT_0058b970[4];
extern "C" void FUN_003c3d90(void);
extern "C" SFUN_003c3d00 *beNDMWLoadIntf2DegiStateList_ResolveMetaObject(void) {
    if (DAT_0058b970[0] == 0 || !DAT_0058b970[0]->ok()) FUN_003c3d90();
    return DAT_0058b970[0];
}
