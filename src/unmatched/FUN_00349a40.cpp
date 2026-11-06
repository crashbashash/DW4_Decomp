extern "C" {
void *beSvFormatApi_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00349a40(void);
}
void FUN_00349a40(void)
{
    igMetaObject_RunStaticInit(beSvFormatApi_Register);
}
