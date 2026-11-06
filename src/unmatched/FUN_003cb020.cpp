extern "C" {
void *beNDMWAfsSetup_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003cb020(void);
}
void FUN_003cb020(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsSetup_Register);
}
