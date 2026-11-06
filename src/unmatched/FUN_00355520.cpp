extern "C" {
void *beModelCtrlMOVERL_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00355520(void);
}
void FUN_00355520(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMOVERL_Register);
}
