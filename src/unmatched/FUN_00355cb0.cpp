extern "C" {
void *beModelCtrlCTRL_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00355cb0(void);
}
void FUN_00355cb0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlCTRL_Register);
}
