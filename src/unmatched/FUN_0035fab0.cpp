extern "C" {
void *beGeneraterDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035fab0(void);
}
void FUN_0035fab0(void)
{
    igMetaObject_RunStaticInit(beGeneraterDataList_Register);
}
