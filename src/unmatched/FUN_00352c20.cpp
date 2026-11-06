extern "C" {
void *beModelCtrlInfoList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00352c20(void);
}
void FUN_00352c20(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoList_Register);
}
