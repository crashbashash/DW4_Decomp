extern "C" {
void *beNDMWPanelWazaInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bd750(void);
}
void FUN_003bd750(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelWazaInfo_Register);
}
