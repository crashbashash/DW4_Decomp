extern "C" {
void *beModelCtrlData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00356950(void);
}
void FUN_00356950(void)
{
    igMetaObject_RunStaticInit(beModelCtrlData_Register);
}
