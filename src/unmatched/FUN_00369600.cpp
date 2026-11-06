extern "C" {
void *beCameraCtrlInfoRamShake_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00369600(void);
}
void FUN_00369600(void)
{
    igMetaObject_RunStaticInit(beCameraCtrlInfoRamShake_Register);
}
