extern "C" {
void *beNDMWMdlPlayer_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bfae0(void);
}
void FUN_003bfae0(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPlayer_Register);
}
