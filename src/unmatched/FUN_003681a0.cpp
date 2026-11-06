extern "C" {
void *beCopyModelCtrl2_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003681a0(void);
}
void FUN_003681a0(void)
{
    igMetaObject_RunStaticInit(beCopyModelCtrl2_Register);
}
