extern "C" {
void *beSvFileFindApi_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00349cc0(void);
}
void FUN_00349cc0(void)
{
    igMetaObject_RunStaticInit(beSvFileFindApi_Register);
}
