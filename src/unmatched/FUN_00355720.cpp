extern "C" {
void *beModelCtrlMOVEEX_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00355720(void);
}
void FUN_00355720(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMOVEEX_Register);
}
