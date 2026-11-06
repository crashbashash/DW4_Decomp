extern "C" {
void *beCameraCtrl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00369a20(void);
}
void FUN_00369a20(void)
{
    igMetaObject_RunStaticInit(beCameraCtrl_Register);
}
