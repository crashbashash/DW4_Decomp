extern "C" {
void *beModelCtrlAIData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00354940(void);
}
void FUN_00354940(void)
{
    igMetaObject_RunStaticInit(beModelCtrlAIData_Register);
}
