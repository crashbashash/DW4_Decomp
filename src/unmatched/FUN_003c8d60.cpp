extern "C" {
void *beNDMWItemWeapon_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c8d60(void);
}
void FUN_003c8d60(void)
{
    igMetaObject_RunStaticInit(beNDMWItemWeapon_Register);
}
