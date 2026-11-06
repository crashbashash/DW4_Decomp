extern "C" {
void *igAdxAfsFile_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003348d0(void);
}
void FUN_003348d0(void)
{
    igMetaObject_RunStaticInit(igAdxAfsFile_Register);
}
