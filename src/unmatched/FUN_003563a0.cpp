extern "C" {
void *beModelCtrlLABEL_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003563a0(void);
}
void FUN_003563a0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlLABEL_Register);
}
