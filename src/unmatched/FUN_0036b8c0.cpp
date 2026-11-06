extern "C" {
void *beAsTargetModelData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036b8c0(void);
}
void FUN_0036b8c0(void)
{
    igMetaObject_RunStaticInit(beAsTargetModelData_Register);
}
