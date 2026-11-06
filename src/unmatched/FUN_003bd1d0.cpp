extern "C" {
void *beNDMWSaveCtrlCtrlData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bd1d0(void);
}
void FUN_003bd1d0(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveCtrlCtrlData_Register);
}
