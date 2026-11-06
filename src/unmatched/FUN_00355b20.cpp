extern "C" {
void *beModelCtrlMSGBOX_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00355b20(void);
}
void FUN_00355b20(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMSGBOX_Register);
}
