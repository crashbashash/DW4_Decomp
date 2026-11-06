extern "C" {
void *beBaseInfoManagerList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036a820(void);
}
void FUN_0036a820(void)
{
    igMetaObject_RunStaticInit(beBaseInfoManagerList_Register);
}
