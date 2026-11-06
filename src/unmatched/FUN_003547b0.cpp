extern "C" {
void *beModelCtrlAIDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003547b0(void);
}
void FUN_003547b0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlAIDataList_Register);
}
