extern "C" {
void *beSvReadMediaApi_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00349430(void);
}
void FUN_00349430(void)
{
    igMetaObject_RunStaticInit(beSvReadMediaApi_Register);
}
