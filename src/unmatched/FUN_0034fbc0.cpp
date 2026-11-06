extern "C" {
void *beModelCtrlSubComBase_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034fbc0(void);
}
void FUN_0034fbc0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlSubComBase_Register);
}
