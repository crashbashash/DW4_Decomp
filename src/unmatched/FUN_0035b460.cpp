extern "C" {
void *beLuaDataObjectist_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035b460(void);
}
void FUN_0035b460(void)
{
    igMetaObject_RunStaticInit(beLuaDataObjectist_Register);
}
