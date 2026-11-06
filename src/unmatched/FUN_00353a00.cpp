extern "C" {
void *beModelCtrlInfoDataHit_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00353a00(void);
}
void FUN_00353a00(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoDataHit_Register);
}
