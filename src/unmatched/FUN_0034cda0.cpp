extern "C" {
void *bePadDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034cda0(void);
}
void FUN_0034cda0(void)
{
    igMetaObject_RunStaticInit(bePadDataList_Register);
}
