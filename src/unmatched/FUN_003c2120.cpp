extern "C" {
void *beNDMWLogoCtrlData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c2120(void);
}
void FUN_003c2120(void)
{
    igMetaObject_RunStaticInit(beNDMWLogoCtrlData_Register);
}
