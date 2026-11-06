extern "C" {
void *beModelCtrlHITBOX_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00354b80(void);
}
void FUN_00354b80(void)
{
    igMetaObject_RunStaticInit(beModelCtrlHITBOX_Register);
}
