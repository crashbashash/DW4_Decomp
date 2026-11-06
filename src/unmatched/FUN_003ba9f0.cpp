extern "C" {
void *beNDMWStatusPowerSocket_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003ba9f0(void);
}
void FUN_003ba9f0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusPowerSocket_Register);
}
