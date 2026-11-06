extern "C" {
void *beFontInfoData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00361210(void);
}
void FUN_00361210(void)
{
    igMetaObject_RunStaticInit(beFontInfoData_Register);
}
