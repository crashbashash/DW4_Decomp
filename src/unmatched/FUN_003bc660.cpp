extern "C" {
void *beSaveIntfComMdlDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bc660(void);
}
void FUN_003bc660(void)
{
    igMetaObject_RunStaticInit(beSaveIntfComMdlDataList_Register);
}
