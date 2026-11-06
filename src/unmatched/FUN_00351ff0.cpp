extern "C" {
void *beModelCtrlInfoRideOn_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00351ff0(void);
}
void FUN_00351ff0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoRideOn_Register);
}
