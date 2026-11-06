extern "C" {
void *beFontImage_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00361c70(void);
}
void FUN_00361c70(void)
{
    igMetaObject_RunStaticInit(beFontImage_Register);
}
