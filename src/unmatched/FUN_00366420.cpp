extern "C" {
void *beCriVolume_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00366420(void);
}
void FUN_00366420(void)
{
    igMetaObject_RunStaticInit(beCriVolume_Register);
}
