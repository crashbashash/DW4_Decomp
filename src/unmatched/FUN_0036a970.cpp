extern "C" {
void *beBaseInfoManager_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036a970(void);
}
void FUN_0036a970(void)
{
    igMetaObject_RunStaticInit(beBaseInfoManager_Register);
}
