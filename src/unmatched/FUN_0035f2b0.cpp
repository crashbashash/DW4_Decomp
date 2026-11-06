extern "C" {
void *beGeneraterInfoWork_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035f2b0(void);
}
void FUN_0035f2b0(void)
{
    igMetaObject_RunStaticInit(beGeneraterInfoWork_Register);
}
