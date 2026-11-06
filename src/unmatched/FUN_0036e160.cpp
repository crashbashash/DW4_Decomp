extern "C" {
void *be_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036e160(void);
}
void FUN_0036e160(void)
{
    igMetaObject_RunStaticInit(be_Register);
}
