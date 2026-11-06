extern "C" {
void *beWeaponInfoRam_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0033ea40(void);
}
void FUN_0033ea40(void)
{
    igMetaObject_RunStaticInit(beWeaponInfoRam_Register);
}
