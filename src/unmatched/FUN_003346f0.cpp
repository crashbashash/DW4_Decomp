extern "C" {
void *igAdxAfsFileList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003346f0(void);
}
void FUN_003346f0(void)
{
    igMetaObject_RunStaticInit(igAdxAfsFileList_Register);
}
