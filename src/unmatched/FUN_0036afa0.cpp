extern "C" {
void *beBaseInfoDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036afa0(void);
}
void FUN_0036afa0(void)
{
    igMetaObject_RunStaticInit(beBaseInfoDataList_Register);
}
