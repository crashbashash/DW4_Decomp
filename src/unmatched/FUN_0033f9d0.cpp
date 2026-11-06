extern "C" {
void *beWeaponAttachDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0033f9d0(void);
}
void FUN_0033f9d0(void)
{
    igMetaObject_RunStaticInit(beWeaponAttachDataList_Register);
}
