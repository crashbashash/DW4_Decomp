extern "C" {
void *beWeaponSeqData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0033f290(void);
}
void FUN_0033f290(void)
{
    igMetaObject_RunStaticInit(beWeaponSeqData_Register);
}
