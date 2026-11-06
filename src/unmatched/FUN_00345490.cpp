extern "C" {
void *beSelectCtrlInfoRamData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00345490(void);
}
void FUN_00345490(void)
{
    igMetaObject_RunStaticInit(beSelectCtrlInfoRamData_Register);
}
