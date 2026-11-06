extern "C" {
void *beModelCtrlInfoDataAIH_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00353cd0(void);
}
void FUN_00353cd0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoDataAIH_Register);
}
