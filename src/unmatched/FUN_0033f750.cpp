extern "C" {
void *beWeapon_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0033f750(void);
}
void FUN_0033f750(void)
{
    igMetaObject_RunStaticInit(beWeapon_Register);
}
