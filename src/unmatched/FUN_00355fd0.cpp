extern "C" {
void *beModelCtrlACTION_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00355fd0(void);
}
void FUN_00355fd0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlACTION_Register);
}
