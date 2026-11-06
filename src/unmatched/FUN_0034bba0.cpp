extern "C" {
void *bePoint01_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034bba0(void);
}
void FUN_0034bba0(void)
{
    igMetaObject_RunStaticInit(bePoint01_Register);
}
