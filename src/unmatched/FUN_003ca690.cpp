extern "C" {
void *beNDMWAfsSetupInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003ca690(void);
}
void FUN_003ca690(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsSetupInfo_Register);
}
