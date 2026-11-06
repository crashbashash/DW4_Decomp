extern "C" {
void *beKeyboardReceiver_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035d1a0(void);
}
void FUN_0035d1a0(void)
{
    igMetaObject_RunStaticInit(beKeyboardReceiver_Register);
}
