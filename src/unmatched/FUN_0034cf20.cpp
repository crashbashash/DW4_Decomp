extern "C" {
void *bePadData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034cf20(void);
}
void FUN_0034cf20(void)
{
    igMetaObject_RunStaticInit(bePadData_Register);
}
