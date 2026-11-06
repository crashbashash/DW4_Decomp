extern "C" {
void *beNDMWPanelWazaInfoRam_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bd9c0(void);
}
void FUN_003bd9c0(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelWazaInfoRam_Register);
}
