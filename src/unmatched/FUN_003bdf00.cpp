extern "C" {
void *beNDMWPanelWazaInfoWork_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bdf00(void);
}
void FUN_003bdf00(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelWazaInfoWork_Register);
}
