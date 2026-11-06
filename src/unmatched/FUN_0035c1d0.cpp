extern "C" {
void *beLightCtrl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035c1d0(void);
}
void FUN_0035c1d0(void)
{
    igMetaObject_RunStaticInit(beLightCtrl_Register);
}
