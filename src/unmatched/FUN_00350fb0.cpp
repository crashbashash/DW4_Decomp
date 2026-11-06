extern "C" {
void *beModelCtrlInfoWork_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00350fb0(void);
}
void FUN_00350fb0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoWork_Register);
}
