extern "C" {
void *beFontInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00360fe0(void);
}
void FUN_00360fe0(void)
{
    igMetaObject_RunStaticInit(beFontInfo_Register);
}
