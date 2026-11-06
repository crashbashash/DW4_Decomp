extern "C" {
void *beWeaponAttachData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0033fbf0(void);
}
void FUN_0033fbf0(void)
{
    igMetaObject_RunStaticInit(beWeaponAttachData_Register);
}
