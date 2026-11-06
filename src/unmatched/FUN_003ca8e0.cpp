extern "C" {
void *beNDMWAfsSetupDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003ca8e0(void);
}
void FUN_003ca8e0(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsSetupDataList_Register);
}
