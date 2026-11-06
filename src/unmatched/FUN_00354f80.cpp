extern "C" {
void *beModelCtrlAIMAP_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00354f80(void);
}
void FUN_00354f80(void)
{
    igMetaObject_RunStaticInit(beModelCtrlAIMAP_Register);
}
