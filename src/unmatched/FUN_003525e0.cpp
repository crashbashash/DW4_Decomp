extern "C" {
void *beModelCtrlInfoHitBody_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003525e0(void);
}
void FUN_003525e0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoHitBody_Register);
}
