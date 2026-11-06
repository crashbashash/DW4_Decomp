extern "C" {
void *beModelCtrlMUTEKI_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00354d80(void);
}
void FUN_00354d80(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMUTEKI_Register);
}
