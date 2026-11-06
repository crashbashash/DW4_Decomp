extern "C" {
void *beSvPs2McImage128k_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00347ce0(void);
}
void FUN_00347ce0(void)
{
    igMetaObject_RunStaticInit(beSvPs2McImage128k_Register);
}
