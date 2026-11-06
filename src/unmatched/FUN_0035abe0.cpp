extern "C" {
void *beLuaState_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035abe0(void);
}
void FUN_0035abe0(void)
{
    igMetaObject_RunStaticInit(beLuaState_Register);
}
