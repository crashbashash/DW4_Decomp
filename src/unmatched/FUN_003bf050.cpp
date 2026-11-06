extern "C" {
void *beNDMWPanelWaza_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bf050(void);
}
void FUN_003bf050(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelWaza_Register);
}
