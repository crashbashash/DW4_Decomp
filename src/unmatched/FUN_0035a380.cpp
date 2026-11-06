extern "C" {
void *beMatCtrlDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035a380(void);
}
void FUN_0035a380(void)
{
    igMetaObject_RunStaticInit(beMatCtrlDataList_Register);
}
