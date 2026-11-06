extern "C" {
void *beMovie_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034f0a0(void);
}
void FUN_0034f0a0(void)
{
    igMetaObject_RunStaticInit(beMovie_Register);
}
