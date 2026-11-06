extern "C" {
void *beAsTargetModelDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036b6e0(void);
}
void FUN_0036b6e0(void)
{
    igMetaObject_RunStaticInit(beAsTargetModelDataList_Register);
}
