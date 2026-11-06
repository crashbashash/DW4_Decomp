extern "C" {
void *beSvEndApi_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003487c0(void);
}
void FUN_003487c0(void)
{
    igMetaObject_RunStaticInit(beSvEndApi_Register);
}
