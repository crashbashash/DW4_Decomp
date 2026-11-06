extern "C" {
void *beCriFxXbData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00367080(void);
}
void FUN_00367080(void)
{
    igMetaObject_RunStaticInit(beCriFxXbData_Register);
}
