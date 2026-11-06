extern "C" {
void *beNDMWMdlItemInfoWork_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c15b0(void);
}
void FUN_003c15b0(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlItemInfoWork_Register);
}
