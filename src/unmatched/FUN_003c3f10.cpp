extern "C" {
void *beNDMWLoadIntf2DegiState_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c3f10(void);
}
void FUN_003c3f10(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2DegiState_Register);
}
