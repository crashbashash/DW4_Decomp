extern "C" {
void *beChangePosTransform_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003688d0(void);
}
void FUN_003688d0(void)
{
    igMetaObject_RunStaticInit(beChangePosTransform_Register);
}
