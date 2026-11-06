extern "C" {
void *beNDMWItemYellowArmor_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c8a40(void);
}
void FUN_003c8a40(void)
{
    igMetaObject_RunStaticInit(beNDMWItemYellowArmor_Register);
}
