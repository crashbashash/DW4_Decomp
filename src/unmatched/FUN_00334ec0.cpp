extern "C" {
void *igAdxFile_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00334ec0(void);
}
void FUN_00334ec0(void)
{
    igMetaObject_RunStaticInit(igAdxFile_Register);
}
