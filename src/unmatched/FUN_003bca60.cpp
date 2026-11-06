extern "C" {
void *beNDMWSaveIntfCtrlData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bca60(void);
}
void FUN_003bca60(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveIntfCtrlData_Register);
}
