extern "C" {
void *beLayerInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035c570(void);
}
void FUN_0035c570(void)
{
    igMetaObject_RunStaticInit(beLayerInfo_Register);
}
