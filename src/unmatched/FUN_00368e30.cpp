extern "C" {
void *beCameraCtrlInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00368e30(void);
}
void FUN_00368e30(void)
{
    igMetaObject_RunStaticInit(beCameraCtrlInfo_Register);
}
