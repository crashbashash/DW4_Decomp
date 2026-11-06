extern "C" {
void *beBaseInfoList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036abd0(void);
}
void FUN_0036abd0(void)
{
    igMetaObject_RunStaticInit(beBaseInfoList_Register);
}
