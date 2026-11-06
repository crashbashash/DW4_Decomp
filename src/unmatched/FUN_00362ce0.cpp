extern "C" {
void *beFileListInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00362ce0(void);
}
void FUN_00362ce0(void)
{
    igMetaObject_RunStaticInit(beFileListInfo_Register);
}
