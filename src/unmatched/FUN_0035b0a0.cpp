extern "C" {
void *beLuaDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035b0a0(void);
}
void FUN_0035b0a0(void)
{
    igMetaObject_RunStaticInit(beLuaDataList_Register);
}
