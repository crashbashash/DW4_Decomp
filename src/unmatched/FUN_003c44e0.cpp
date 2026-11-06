extern "C" {
void *beNDMWLoadIntf2CtrlData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c44e0(void);
}
void FUN_003c44e0(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2CtrlData_Register);
}
