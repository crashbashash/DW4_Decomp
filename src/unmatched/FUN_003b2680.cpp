extern "C" {
void *beNDMWTitle2CtrlData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b2680(void);
}
void FUN_003b2680(void)
{
    igMetaObject_RunStaticInit(beNDMWTitle2CtrlData_Register);
}
