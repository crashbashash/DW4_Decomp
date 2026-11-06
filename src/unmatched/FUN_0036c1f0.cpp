extern "C" {
void *beActionStarter_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036c1f0(void);
}
void FUN_0036c1f0(void)
{
    igMetaObject_RunStaticInit(beActionStarter_Register);
}
