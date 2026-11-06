extern "C" {
void *beLayerInfoRam_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035c370(void);
}
void FUN_0035c370(void)
{
    igMetaObject_RunStaticInit(beLayerInfoRam_Register);
}
