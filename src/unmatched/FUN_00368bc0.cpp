extern "C" {
void *beCameraMode_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00368bc0(void);
}
void FUN_00368bc0(void)
{
    igMetaObject_RunStaticInit(beCameraMode_Register);
}
