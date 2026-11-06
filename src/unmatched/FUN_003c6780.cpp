extern "C" {
void *beNDMWDegiDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c6780(void);
}
void FUN_003c6780(void)
{
    igMetaObject_RunStaticInit(beNDMWDegiDataList_Register);
}
