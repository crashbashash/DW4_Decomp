extern "C" {
void *beLayerGroup_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035c930(void);
}
void FUN_0035c930(void)
{
    igMetaObject_RunStaticInit(beLayerGroup_Register);
}
