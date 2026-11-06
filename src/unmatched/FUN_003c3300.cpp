extern "C" {
void *beNDMWLoadIntf2Diffselect_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c3300(void);
}
void FUN_003c3300(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2Diffselect_Register);
}
