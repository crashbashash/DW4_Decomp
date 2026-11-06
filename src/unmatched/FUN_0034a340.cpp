extern "C" {
void *beSvPlatBaseData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034a340(void);
}
void FUN_0034a340(void)
{
    igMetaObject_RunStaticInit(beSvPlatBaseData_Register);
}
