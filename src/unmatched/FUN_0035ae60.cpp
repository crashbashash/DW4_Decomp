extern "C" {
void *beLuaInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035ae60(void);
}
void FUN_0035ae60(void)
{
    igMetaObject_RunStaticInit(beLuaInfo_Register);
}
