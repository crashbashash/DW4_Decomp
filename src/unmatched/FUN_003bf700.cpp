extern "C" {
void *beNDMWMdlPlayer2InfoWork_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bf700(void);
}
void FUN_003bf700(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPlayer2InfoWork_Register);
}
