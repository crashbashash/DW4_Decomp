extern "C" {
void *beNDMWLoadIntf2_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c4850(void);
}
void FUN_003c4850(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2_Register);
}
