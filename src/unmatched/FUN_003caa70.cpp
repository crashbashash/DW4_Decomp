extern "C" {
void *beNDMWAfsSetupData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003caa70(void);
}
void FUN_003caa70(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsSetupData_Register);
}
