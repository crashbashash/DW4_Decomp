extern "C" {
void *beTextureCtrlAttr_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00341f40(void);
}
void FUN_00341f40(void)
{
    igMetaObject_RunStaticInit(beTextureCtrlAttr_Register);
}
