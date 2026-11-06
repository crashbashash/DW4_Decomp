extern "C" {
void *beNDMWAfsStageLoad_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003cac70(void);
}
void FUN_003cac70(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsStageLoad_Register);
}
