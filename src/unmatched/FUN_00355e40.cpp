extern "C" {
void *beModelCtrlJUMP_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00355e40(void);
}
void FUN_00355e40(void)
{
    igMetaObject_RunStaticInit(beModelCtrlJUMP_Register);
}
