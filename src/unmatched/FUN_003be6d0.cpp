extern "C" {
void *beNDMWPanelObjectItem_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003be6d0(void);
}
void FUN_003be6d0(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelObjectItem_Register);
}
