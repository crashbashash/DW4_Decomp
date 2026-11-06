extern "C" {
void *beTextureCtrlInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00341cb0(void);
}
void FUN_00341cb0(void)
{
    igMetaObject_RunStaticInit(beTextureCtrlInfo_Register);
}
