extern "C" {
void *beLoadIntf2ComMdlDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c73a0(void);
}
void FUN_003c73a0(void)
{
    igMetaObject_RunStaticInit(beLoadIntf2ComMdlDataList_Register);
}
