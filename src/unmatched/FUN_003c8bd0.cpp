extern "C" {
void *beNDMWItemBlueArmor_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c8bd0(void);
}
void FUN_003c8bd0(void)
{
    igMetaObject_RunStaticInit(beNDMWItemBlueArmor_Register);
}
