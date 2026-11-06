extern "C" {
void *beSvStartApi_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00348b00(void);
}
void FUN_00348b00(void)
{
    igMetaObject_RunStaticInit(beSvStartApi_Register);
}
