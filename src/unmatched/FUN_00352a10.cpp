extern "C" {
void *beModelCtrlMoveObject_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00352a10(void);
}
void FUN_00352a10(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMoveObject_Register);
}
