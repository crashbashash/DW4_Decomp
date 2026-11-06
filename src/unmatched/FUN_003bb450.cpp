extern "C" {
void *beNDMWListCtrl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bb450(void);
}
void FUN_003bb450(void)
{
    igMetaObject_RunStaticInit(beNDMWListCtrl_Register);
}
