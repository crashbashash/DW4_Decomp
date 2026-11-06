extern "C" {
void *beActionStarterDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036bd40(void);
}
void FUN_0036bd40(void)
{
    igMetaObject_RunStaticInit(beActionStarterDataList_Register);
}
