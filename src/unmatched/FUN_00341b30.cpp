extern "C" {
void *beTextureCtrlInfoList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00341b30(void);
}
void FUN_00341b30(void)
{
    igMetaObject_RunStaticInit(beTextureCtrlInfoList_Register);
}
