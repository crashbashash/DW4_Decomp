extern "C" {
void *beNDMWMdlPlayer2_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bf3f0(void);
}
void FUN_003bf3f0(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPlayer2_Register);
}
