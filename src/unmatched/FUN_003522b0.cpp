extern "C" {
void *beModelCtrlInfoAI_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003522b0(void);
}
void FUN_003522b0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoAI_Register);
}
