extern "C" {
void *beSvFileMakeApi_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00349e90(void);
}
void FUN_00349e90(void)
{
    igMetaObject_RunStaticInit(beSvFileMakeApi_Register);
}
