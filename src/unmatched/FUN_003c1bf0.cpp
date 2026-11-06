extern "C" {
void *beNDMWMdlEffect_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c1bf0(void);
}
void FUN_003c1bf0(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlEffect_Register);
}
