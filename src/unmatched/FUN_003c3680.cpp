extern "C" {
void *beNDMWLoadIntf2DataSelIntf_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c3680(void);
}
void FUN_003c3680(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2DataSelIntf_Register);
}
