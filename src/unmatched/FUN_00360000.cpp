extern "C" {
void *beGeneraterPlayerDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00360000(void);
}
void FUN_00360000(void)
{
    igMetaObject_RunStaticInit(beGeneraterPlayerDataList_Register);
}
