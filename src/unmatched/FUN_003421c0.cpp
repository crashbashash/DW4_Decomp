extern "C" {
void *beTextureCtrlData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003421c0(void);
}
void FUN_003421c0(void)
{
    igMetaObject_RunStaticInit(beTextureCtrlData_Register);
}
