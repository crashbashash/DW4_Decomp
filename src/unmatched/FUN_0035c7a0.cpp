extern "C" {
void *beLayerGroupList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035c7a0(void);
}
void FUN_0035c7a0(void)
{
    igMetaObject_RunStaticInit(beLayerGroupList_Register);
}
