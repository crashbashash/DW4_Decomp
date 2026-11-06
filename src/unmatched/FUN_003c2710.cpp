extern "C" {
void *beNDMWLoadIntf2Info_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c2710(void);
}
void FUN_003c2710(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2Info_Register);
}
