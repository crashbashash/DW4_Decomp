extern "C" {
void *beNDMWItemWaza_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c8110(void);
}
void FUN_003c8110(void)
{
    igMetaObject_RunStaticInit(beNDMWItemWaza_Register);
}
