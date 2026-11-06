extern "C" {
void *libNdmwRuntimePlugin_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b18b0(void);
}
void FUN_003b18b0(void)
{
    igMetaObject_RunStaticInit(libNdmwRuntimePlugin_Register);
}
