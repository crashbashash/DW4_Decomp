extern "C" {
void *beLayerCtl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035cbf0(void);
}
void FUN_0035cbf0(void)
{
    igMetaObject_RunStaticInit(beLayerCtl_Register);
}
