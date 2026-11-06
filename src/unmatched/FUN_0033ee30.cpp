extern "C" {
void *beWeaponInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0033ee30(void);
}
void FUN_0033ee30(void)
{
    igMetaObject_RunStaticInit(beWeaponInfo_Register);
}
