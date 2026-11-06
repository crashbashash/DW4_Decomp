extern "C" {
void *beModelCtrlSubCom_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034f340(void);
}
void FUN_0034f340(void)
{
    igMetaObject_RunStaticInit(beModelCtrlSubCom_Register);
}
