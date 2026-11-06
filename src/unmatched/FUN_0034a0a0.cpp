extern "C" {
void *beSaveApi_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034a0a0(void);
}
void FUN_0034a0a0(void)
{
    igMetaObject_RunStaticInit(beSaveApi_Register);
}
