extern "C" {
void *beNDMWPanelObjectStat_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003be360(void);
}
void FUN_003be360(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelObjectStat_Register);
}
