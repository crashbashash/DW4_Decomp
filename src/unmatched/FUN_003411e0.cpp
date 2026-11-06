extern "C" {
void *beTransformSync_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003411e0(void);
}
void FUN_003411e0(void)
{
    igMetaObject_RunStaticInit(beTransformSync_Register);
}
