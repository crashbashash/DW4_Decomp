extern "C" {
void *beLightCtrlInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035be50(void);
}
void FUN_0035be50(void)
{
    igMetaObject_RunStaticInit(beLightCtrlInfo_Register);
}
