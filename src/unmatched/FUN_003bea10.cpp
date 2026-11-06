extern "C" {
void *beNDMWPanelObjectWaza_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bea10(void);
}
void FUN_003bea10(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelObjectWaza_Register);
}
