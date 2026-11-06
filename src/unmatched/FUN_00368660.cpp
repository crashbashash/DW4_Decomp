extern "C" {
void *beChangePosTransformInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00368660(void);
}
void FUN_00368660(void)
{
    igMetaObject_RunStaticInit(beChangePosTransformInfo_Register);
}
