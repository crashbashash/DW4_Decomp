extern "C" {
void *beMatCtrlData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035a560(void);
}
void FUN_0035a560(void)
{
    igMetaObject_RunStaticInit(beMatCtrlData_Register);
}
