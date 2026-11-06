extern "C" {
void *beSvPlatDataPS2_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00347970(void);
}
void FUN_00347970(void)
{
    igMetaObject_RunStaticInit(beSvPlatDataPS2_Register);
}
