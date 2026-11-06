extern "C" {
void *beTextureCtrl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003424e0(void);
}
void FUN_003424e0(void)
{
    igMetaObject_RunStaticInit(beTextureCtrl_Register);
}
