extern "C" {
void *beSeInfoData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00345fd0(void);
}
void FUN_00345fd0(void)
{
    igMetaObject_RunStaticInit(beSeInfoData_Register);
}
