extern "C" {
void *igLightSetList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035bc50(void);
}
void FUN_0035bc50(void)
{
    igMetaObject_RunStaticInit(igLightSetList_Register);
}
