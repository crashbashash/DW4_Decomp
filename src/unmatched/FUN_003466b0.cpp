extern "C" {
void *beSeCtl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003466b0(void);
}
void FUN_003466b0(void)
{
    igMetaObject_RunStaticInit(beSeCtl_Register);
}
