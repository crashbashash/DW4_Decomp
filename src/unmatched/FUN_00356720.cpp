extern "C" {
void *beModelCtrlDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00356720(void);
}
void FUN_00356720(void)
{
    igMetaObject_RunStaticInit(beModelCtrlDataList_Register);
}
