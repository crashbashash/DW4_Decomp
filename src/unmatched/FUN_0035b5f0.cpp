extern "C" {
void *beLuaDataObject_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035b5f0(void);
}
void FUN_0035b5f0(void)
{
    igMetaObject_RunStaticInit(beLuaDataObject_Register);
}
