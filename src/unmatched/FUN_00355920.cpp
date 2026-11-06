extern "C" {
void *beModelCtrlMOVE_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00355920(void);
}
void FUN_00355920(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMOVE_Register);
}
