extern "C" {
void *beModelCtrlInfoDataTrc_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003533c0(void);
}
void FUN_003533c0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoDataTrc_Register);
}
