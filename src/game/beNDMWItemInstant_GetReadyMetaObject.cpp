struct SFUN_003c8400 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_003c8400 *DAT_0058bf28[4];
extern "C" void FUN_003c8490(void);
extern "C" SFUN_003c8400 *beNDMWItemInstant_GetReadyMetaObject(void) {
    if (DAT_0058bf28[0] == 0 || !DAT_0058bf28[0]->ok()) FUN_003c8490();
    return DAT_0058bf28[0];
}
