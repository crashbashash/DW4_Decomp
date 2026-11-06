extern "C" {
void *beTimerDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00341790(void);
}
void FUN_00341790(void)
{
    igMetaObject_RunStaticInit(beTimerDataList_Register);
}
