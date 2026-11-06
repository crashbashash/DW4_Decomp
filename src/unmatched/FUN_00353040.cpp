extern "C" {
void *beModelCtrlInfoRamData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00353040(void);
}
void FUN_00353040(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoRamData_Register);
}
