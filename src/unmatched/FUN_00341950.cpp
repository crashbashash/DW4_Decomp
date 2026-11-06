extern "C" {
void *beTimerData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00341950(void);
}
void FUN_00341950(void)
{
    igMetaObject_RunStaticInit(beTimerData_Register);
}
