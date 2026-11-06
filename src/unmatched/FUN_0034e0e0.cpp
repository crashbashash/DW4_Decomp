extern "C" {
void *beNumberCtrlInfoList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034e0e0(void);
}
void FUN_0034e0e0(void)
{
    igMetaObject_RunStaticInit(beNumberCtrlInfoList_Register);
}
