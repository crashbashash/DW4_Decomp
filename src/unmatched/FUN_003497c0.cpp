extern "C" {
void *beSvUseCheckApi_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003497c0(void);
}
void FUN_003497c0(void)
{
    igMetaObject_RunStaticInit(beSvUseCheckApi_Register);
}
