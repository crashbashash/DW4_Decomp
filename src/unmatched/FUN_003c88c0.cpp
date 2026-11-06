extern "C" {
void *beNDMWItemAbilityChip_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c88c0(void);
}
void FUN_003c88c0(void)
{
    igMetaObject_RunStaticInit(beNDMWItemAbilityChip_Register);
}
