extern "C" {
void *beFileListInfoManager_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003629b0(void);
}
void FUN_003629b0(void)
{
    igMetaObject_RunStaticInit(beFileListInfoManager_Register);
}
