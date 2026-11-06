extern "C" {
void *libBecRuntimePlugin_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0033e350(void);
}
void FUN_0033e350(void)
{
    igMetaObject_RunStaticInit(libBecRuntimePlugin_Register);
}
