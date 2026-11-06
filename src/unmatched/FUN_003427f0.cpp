extern "C" {
void *beTextureCtrlWork_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003427f0(void);
}
void FUN_003427f0(void)
{
    igMetaObject_RunStaticInit(beTextureCtrlWork_Register);
}
