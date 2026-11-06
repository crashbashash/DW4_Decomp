extern "C" {
void *beSvGetFreeSizeApi_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00348e40(void);
}
void FUN_00348e40(void)
{
    igMetaObject_RunStaticInit(beSvGetFreeSizeApi_Register);
}
