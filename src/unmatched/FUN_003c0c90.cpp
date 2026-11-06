extern "C" {
void *beNDMWMdlObject_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c0c90(void);
}
void FUN_003c0c90(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlObject_Register);
}
