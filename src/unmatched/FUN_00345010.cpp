extern "C" {
void *beShadow01_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00345010(void);
}
void FUN_00345010(void)
{
    igMetaObject_RunStaticInit(beShadow01_Register);
}
