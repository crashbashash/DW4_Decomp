extern "C" {
void *beMeterCtrlOneData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00357450(void);
}
void FUN_00357450(void)
{
    igMetaObject_RunStaticInit(beMeterCtrlOneData_Register);
}
