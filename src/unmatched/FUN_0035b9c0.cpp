extern "C" {
void *beLua_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035b9c0(void);
}
void FUN_0035b9c0(void)
{
    igMetaObject_RunStaticInit(beLua_Register);
}
