extern "C" {
void *beModelCtrlInfoDataSeq_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003536e0(void);
}
void FUN_003536e0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoDataSeq_Register);
}
