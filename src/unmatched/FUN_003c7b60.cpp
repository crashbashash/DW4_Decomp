extern "C" {
void *beNDMWLoadCtrl2CtrlData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c7b60(void);
}
void FUN_003c7b60(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadCtrl2CtrlData_Register);
}
