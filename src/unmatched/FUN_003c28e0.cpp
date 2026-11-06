extern "C" {
void *beNDMWLoadIntf2NameSel_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c28e0(void);
}
void FUN_003c28e0(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2NameSel_Register);
}
