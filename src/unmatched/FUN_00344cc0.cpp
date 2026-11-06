extern "C" {
void *beShadow01Info_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00344cc0(void);
}
void FUN_00344cc0(void)
{
    igMetaObject_RunStaticInit(beShadow01Info_Register);
}
