extern "C" {
void *beLuaData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035b280(void);
}
void FUN_0035b280(void)
{
    igMetaObject_RunStaticInit(beLuaData_Register);
}
