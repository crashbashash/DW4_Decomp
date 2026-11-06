extern "C" {
void *beNDMWPanelObject_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bec70(void);
}
void FUN_003bec70(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelObject_Register);
}
