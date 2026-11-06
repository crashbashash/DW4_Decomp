extern "C" {
void *beModelCtrlLUACALL_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00356570(void);
}
void FUN_00356570(void)
{
    igMetaObject_RunStaticInit(beModelCtrlLUACALL_Register);
}
