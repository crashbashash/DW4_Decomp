extern "C" {
void *beSvWriteMediaApi_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00349100(void);
}
void FUN_00349100(void)
{
    igMetaObject_RunStaticInit(beSvWriteMediaApi_Register);
}
