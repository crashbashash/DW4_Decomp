extern "C" {
void *beNDMWMdlPEBase_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c0550(void);
}
void FUN_003c0550(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPEBase_Register);
}
