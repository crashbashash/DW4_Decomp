extern "C" {
void *bePoint01Info_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034b810(void);
}
void FUN_0034b810(void)
{
    igMetaObject_RunStaticInit(bePoint01Info_Register);
}
