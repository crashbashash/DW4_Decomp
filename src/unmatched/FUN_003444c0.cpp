extern "C" {
void *beSound_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003444c0(void);
}
void FUN_003444c0(void)
{
    igMetaObject_RunStaticInit(beSound_Register);
}
