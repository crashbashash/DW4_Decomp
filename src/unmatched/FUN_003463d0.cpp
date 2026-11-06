extern "C" {
void *beSeData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003463d0(void);
}
void FUN_003463d0(void)
{
    igMetaObject_RunStaticInit(beSeData_Register);
}
