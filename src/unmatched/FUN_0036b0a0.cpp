extern "C" {
void *beBaseInfoData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036b0a0(void);
}
void FUN_0036b0a0(void)
{
    igMetaObject_RunStaticInit(beBaseInfoData_Register);
}
