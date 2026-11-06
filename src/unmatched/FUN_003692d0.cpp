extern "C" {
void *beCameraBoxData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003692d0(void);
}
void FUN_003692d0(void)
{
    igMetaObject_RunStaticInit(beCameraBoxData_Register);
}
