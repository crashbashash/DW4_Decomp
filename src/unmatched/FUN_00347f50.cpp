extern "C" {
void *beSvPlatDataGC_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00347f50(void);
}
void FUN_00347f50(void)
{
    igMetaObject_RunStaticInit(beSvPlatDataGC_Register);
}
