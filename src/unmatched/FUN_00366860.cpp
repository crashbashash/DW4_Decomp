extern "C" {
void *beCriHandleList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00366860(void);
}
void FUN_00366860(void)
{
    igMetaObject_RunStaticInit(beCriHandleList_Register);
}
