extern "C" {
void *beNDMWWindowCtrl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bb610(void);
}
void FUN_003bb610(void)
{
    igMetaObject_RunStaticInit(beNDMWWindowCtrl_Register);
}
