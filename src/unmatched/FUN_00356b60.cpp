extern "C" {
void *beModelCtrl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00356b60(void);
}
void FUN_00356b60(void)
{
    igMetaObject_RunStaticInit(beModelCtrl_Register);
}
