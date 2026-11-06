extern "C" {
void *beChangePosTransformInfoRam_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00368450(void);
}
void FUN_00368450(void)
{
    igMetaObject_RunStaticInit(beChangePosTransformInfoRam_Register);
}
