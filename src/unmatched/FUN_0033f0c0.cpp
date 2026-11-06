extern "C" {
void *beWeaponSeqDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0033f0c0(void);
}
void FUN_0033f0c0(void)
{
    igMetaObject_RunStaticInit(beWeaponSeqDataList_Register);
}
