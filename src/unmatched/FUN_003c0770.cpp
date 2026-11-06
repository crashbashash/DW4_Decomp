extern "C" {
void *beNDMWMdlPEBaseInfoWork_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c0770(void);
}
void FUN_003c0770(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPEBaseInfoWork_Register);
}
