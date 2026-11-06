extern "C" {
void *beNDMWMdlMapBase_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c1070(void);
}
void FUN_003c1070(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlMapBase_Register);
}
