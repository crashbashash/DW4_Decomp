extern "C" {
void *beModelCtrlInfoDataAIM_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00353fc0(void);
}
void FUN_00353fc0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoDataAIM_Register);
}
