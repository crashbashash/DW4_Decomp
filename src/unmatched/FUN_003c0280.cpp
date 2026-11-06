extern "C" {
void *beNDMWMdlPlayerInfoWork_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c0280(void);
}
void FUN_003c0280(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPlayerInfoWork_Register);
}
