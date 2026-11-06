extern "C" {
void *beXboxImage24k_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003476e0(void);
}
void FUN_003476e0(void)
{
    igMetaObject_RunStaticInit(beXboxImage24k_Register);
}
