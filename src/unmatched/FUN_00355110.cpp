extern "C" {
void *beModelCtrlWCHECK_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00355110(void);
}
void FUN_00355110(void)
{
    igMetaObject_RunStaticInit(beModelCtrlWCHECK_Register);
}
