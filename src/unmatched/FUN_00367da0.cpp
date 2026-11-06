extern "C" {
void *beCountry_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00367da0(void);
}
void FUN_00367da0(void)
{
    igMetaObject_RunStaticInit(beCountry_Register);
}
