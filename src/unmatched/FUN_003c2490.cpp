extern "C" {
void *beNDMWLogo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c2490(void);
}
void FUN_003c2490(void)
{
    igMetaObject_RunStaticInit(beNDMWLogo_Register);
}
