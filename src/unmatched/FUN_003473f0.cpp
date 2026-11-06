extern "C" {
void *beSvPlatDataXbox_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003473f0(void);
}
void FUN_003473f0(void)
{
    igMetaObject_RunStaticInit(beSvPlatDataXbox_Register);
}
